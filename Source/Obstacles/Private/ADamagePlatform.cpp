// Fill out your copyright notice in the Description page of Project Settings.


#include "ADamagePlatform.h"

#include "Platformer/PlatformerCharacter.h"

void AADamagePlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
		this->PlaySound(0.81f);
		this->MakeDamage(Character, DamageTypes::Normal);
	}
}
