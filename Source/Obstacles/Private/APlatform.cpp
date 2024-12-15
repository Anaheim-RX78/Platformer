// Fill out your copyright notice in the Description page of Project Settings.

#include "APlatform.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAPlatform::AAPlatform()
{
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
void AAPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void AAPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Common platform detected! Please override this method!"));
}

void AAPlatform::TakeDamage(APlatformerCharacter* Character, const DamageTypes DamageType) const
{
	if (!IsEnabled)
	{
		return;
	}

	const int Damage = GetDamage(Character, DamageType);

	if (Character->Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You are already died!"));
	}
	else if (Damage >= Character->Health)
	{
		Character->Health = 0;
		// Game Over
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You are died!"));
	}
	else if (Damage < Character->Health)
	{
		Character->Health -= Damage;
		if (DamageSoundEffect)
		{
			UGameplayStatics::PlaySound2D(this, DamageSoundEffect, 1.0f, 1.0f, 0.81f);
		}

		if (Character->Health < 0)
		{
			Character->Health = 0;
			// Game Over
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You are died!"));
			return;
		}

		const FString Message = FString::Printf(
			TEXT("You got %d damage! Remaining HP: %d / 100"), Damage, Character->Health);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
	}
}

int AAPlatform::GetDamage(const APlatformerCharacter* Character, const DamageTypes DamageType)
{
	if (DamageType == DamageTypes::Normal)
	{
		return FMath::RandRange(1, 10);
	}

	if (DamageType == DamageTypes::Trap)
	{
		return FMath::RandRange(11, 20);
	}

	if (DamageType == DamageTypes::Void)
	{
		return Character->Health;
	}

	if (DamageType == DamageTypes::Poison)
	{
		// TODO: Set poisoned status
	}

	return 0;
}

// Called every frame
void AAPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
