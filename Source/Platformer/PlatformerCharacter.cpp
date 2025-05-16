// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APlatformerCharacter::APlatformerCharacter() {
	this->GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationRoll = false;

	this->GetCharacterMovement()->bOrientRotationToMovement = true;
	this->GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	this->GetCharacterMovement()->JumpZVelocity = 700.f;
	this->GetCharacterMovement()->AirControl = 0.35f;
	this->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	this->GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	this->GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	this->GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	this->CameraBoom = this->CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	this->CameraBoom->SetupAttachment(RootComponent);
	this->CameraBoom->TargetArmLength = 400.0f;
	this->CameraBoom->bUsePawnControlRotation = true;

	this->FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	this->FollowCamera->SetupAttachment(this->CameraBoom, USpringArmComponent::SocketName);
	this->FollowCamera->bUsePawnControlRotation = false;
}

void APlatformerCharacter::BeginPlay() {
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this->Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		this->MyLocalPlayerSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UMyLocalPlayerSubsystem>();
	}

	this->MyGameInstanceSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<
		UMyGameInstanceSubsystem>();
}

void APlatformerCharacter::Tick(const float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	this->MyGameInstanceSubsystem->IncreaseTimeElapsed(DeltaSeconds);

	const FVector CurrentLocation = GetActorLocation();

	this->MyLocalPlayerSubsystem->IncreaseDistanceMoved(FVector::Dist(PreviousLocation, CurrentLocation));

	this->PreviousLocation = CurrentLocation;

	if (this->PoisonDurationInSeconds == 0) {
		return;
	}

	this->MyGameInstanceSubsystem->IncreaseTimeElapsed(DeltaSeconds);

	if (this->MyGameInstanceSubsystem->GetTimeElapsed() >= this->PoisonDurationInSeconds) {
		this->MyLocalPlayerSubsystem->ReduceHealth(FMath::RandRange(1, 5));
		this->PoisonDurationInSeconds--;
		if (this->PoisonDurationInSeconds == 0) {
			this->IsPoisoned = false;
		}
	}
}

void APlatformerCharacter::GetDamage(const int Damage) {
	if (this->MyLocalPlayerSubsystem->GetHealth() == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player is already died!"));
	} else if (Damage >= this->MyLocalPlayerSubsystem->GetHealth()) {
		this->MyLocalPlayerSubsystem->ResetHealth();
		// Game Over
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player has died!"));
	} else if (Damage < this->MyLocalPlayerSubsystem->GetHealth()) {
		this->ReduceHealth(Damage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Player got %d damage!"));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlatformerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlatformerCharacter::Look);
	} else {
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void APlatformerCharacter::JumpAndIncreaseCounter(const FInputActionValue& Value) {
	this->Jump();
	if (!this->GetCharacterMovement()->IsFalling()) {
		this->IncreaseJumpCount();
	}
}

void APlatformerCharacter::Move(const FInputActionValue& Value) {
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (this->Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		this->AddMovementInput(ForwardDirection, MovementVector.Y);
		this->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlatformerCharacter::Look(const FInputActionValue& Value) {
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlatformerCharacter::IncreaseDistanceMoved(const float DeltaDistance) {
	this->TotalDistanceMoved += DeltaDistance;
	GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Distance moved: %.2f"), TotalDistanceMoved));
}

void APlatformerCharacter::ReduceHealth(int DeltaHealth) {
	this->Health -= DeltaHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health reduced by %d"), DeltaHealth));
}

void APlatformerCharacter::ResetHealth() {
	this->Health = 0;
	this->DeathCount++;
	this->MyGameInstanceSubsystem->IncreaseDeathCount();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Health reset to 0"));
}

void APlatformerCharacter::IncreaseJumpCount() {
	this->JumpCount++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Jump count increased to %d"), JumpCount));
}
