// Fill out your copyright notice in the Description page of Project Settings.


#include "ATrapPlatform.h"

AATrapPlatform::AATrapPlatform()
{
	this->Trap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap"));
	this->Trap->SetupAttachment(Mesh);
	this->Trap->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Trap->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AATrapPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


	if (!IsEnabled)
	{
		return;
	}

	APlatformerCharacter* Character = static_cast<APlatformerCharacter*>(OtherActor);
	if (IsValid(Character))
	{
		if (FMath::RandBool())
		{
			this->Trap->SetVisibility(true);
			this->PlaySound(0.f);
			this->MakeDamage(Character, DamageTypes::Trap);
		}
	}
}
