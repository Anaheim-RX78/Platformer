// Fill out your copyright notice in the Description page of Project Settings.

#include "APlatform.h"

#include "Components/BoxComponent.h"

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

void AAPlatform::GetDamage(APlatformerCharacter* Character, int Damage)
{
	if (Character->Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player is already died!"));
	}
	else if (Damage >= Character->Health)
	{
		Character->Health = 0;
		// Game Over
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player has died!"));
	}
	else if (Damage < Character->Health)
	{
		Character->Health -= Damage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
		                                 FString::Printf(TEXT("Player got %d damage!"), Damage));
	}
}

// Called every frame
void AAPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
