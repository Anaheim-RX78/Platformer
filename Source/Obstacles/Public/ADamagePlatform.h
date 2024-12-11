// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AMovingPlatform.h"
#include "ADamagePlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AADamagePlatform : public AAMovingPlatform
{
	GENERATED_BODY()

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	static int GetRandomDamage();
};
