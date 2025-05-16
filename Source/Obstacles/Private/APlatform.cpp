// Fill out your copyright notice in the Description page of Project Settings.

#include "APlatform.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAPlatform::AAPlatform() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	// Create and set up the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Mesh);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetRelativeScale3D(FVector(0.8f, 0.8f, 2.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAPlatform::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AAPlatform::BeginPlay() {
	Super::BeginPlay();
}

void AAPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Invalid collision method! Use the correct class!"));
}

void AAPlatform::PlaySound(const float StartTime) const {
	if (DamageSoundEffect) {
		UGameplayStatics::PlaySound2D(this, DamageSoundEffect, 1.0f, 1.0f, StartTime);
	}
}

void AAPlatform::MakeDamage(APlatformerCharacter* Character, const DamageTypes DamageType) const {
	if (!IsEnabled) {
		return;
	}

	const int Damage = GetDamage(Character, DamageType);

	if (Character->MyLocalPlayerSubsystem->GetHealth() == 0) {
		return;
	}
	if (Damage >= Character->MyLocalPlayerSubsystem->GetHealth()) {
		Character->MyLocalPlayerSubsystem->ResetHealth();
	} else if (Damage < Character->MyLocalPlayerSubsystem->GetHealth()) {
		Character->MyLocalPlayerSubsystem->ReduceHealth(Damage);

		if (Character->MyLocalPlayerSubsystem->GetHealth() < 0) {
			Character->MyLocalPlayerSubsystem->ResetHealth();
		}
	}
}

int AAPlatform::GetDamage(APlatformerCharacter* Character, const DamageTypes DamageType) {
	if (DamageType == DamageTypes::Normal) {
		return FMath::RandRange(1, 10);
	}

	if (DamageType == DamageTypes::Trap) {
		return FMath::RandRange(11, 20);
	}

	if (DamageType == DamageTypes::Void) {
		return Character->MyLocalPlayerSubsystem->GetHealth();
	}

	if (DamageType == DamageTypes::Poison) {
		Character->IsPoisoned = true;
		Character->PoisonDurationInSeconds = FMath::RandRange(2, 5);

		return FMath::RandRange(1, 5);
	}

	return 0;
}

// Called every frame
void AAPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
