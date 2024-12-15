// Fill out your copyright notice in the Description page of Project Settings.


#include "AVoidPlatform.h"

void AAVoidPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (!IsEnabled)
	{
		return;
	}

	APlatformerCharacter* Character = static_cast<APlatformerCharacter*>(OtherActor);
	if (IsValid(Character))
	{
		PlaySound(0.f);
		this->TakeDamage(Character, DamageTypes::Void);
	}
}
