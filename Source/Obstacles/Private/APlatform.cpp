// Fill out your copyright notice in the Description page of Project Settings.

#include "APlatform.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AAPlatform::AAPlatform() {
	this->PrimaryActorTick.bCanEverTick = true;

	this->Mesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->SetRootComponent(Mesh);

	this->CollisionBox = this->CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	this->CollisionBox->SetupAttachment(Mesh);
	this->CollisionBox->SetGenerateOverlapEvents(true);
	this->CollisionBox->SetRelativeScale3D(FVector(0.8f, 0.8f, 2.f));
	this->CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAPlatform::OnBeginOverlap);
}

void AAPlatform::BeginPlay() {
	Super::BeginPlay();
}

void AAPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult) {
	APlatformerCharacter* Character = static_cast<APlatformerCharacter*>(OtherActor);
	if (IsValid(Character)) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid collision method! Use the correct class!"));
	}
}

void AAPlatform::PlaySound(const float StartTime) const {
	if (this->DamageSoundEffect) {
		UGameplayStatics::PlaySound2D(this, this->DamageSoundEffect, 1.0f, 1.0f, StartTime);
	}
}

void AAPlatform::MakeDamage(APlatformerCharacter* Character, const EDamageTypes DamageType) const {
	if (!this->IsEnabled) {
		return;
	}

	const int Damage = this->GetDamage(Character, DamageType);

	if (Character->Stats->GetHealth() == 0) {
		return;
	}
	if (Damage >= Character->Stats->GetHealth()) {
		Character->Stats->ResetHealth();
	} else if (Damage < Character->Stats->GetHealth()) {
		Character->Stats->ReduceHealth(Damage);

		if (Character->Stats->GetHealth() < 0) {
			Character->Stats->ResetHealth();
		}
	}
}

int AAPlatform::GetDamage(APlatformerCharacter* Character, const EDamageTypes DamageType) {
	if (DamageType == EDamageTypes::Normal) {
		return FMath::RandRange(1, 10);
	}

	if (DamageType == EDamageTypes::Trap) {
		return FMath::RandRange(11, 20);
	}

	if (DamageType == EDamageTypes::Void) {
		return Character->Stats->GetHealth();
	}

	if (DamageType == EDamageTypes::Poison) {
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
