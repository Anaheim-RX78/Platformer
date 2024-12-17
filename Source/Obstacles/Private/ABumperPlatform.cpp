// Fill out your copyright notice in the Description page of Project Settings.


#include "ABumperPlatform.h"

void AABumperPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
		this->PlaySound(0.f);
	}
}
