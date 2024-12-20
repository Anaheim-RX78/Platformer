// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AMovingPlatform.h"
#include "APoisonPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AAPoisonPlatform : public AAMovingPlatform
{
	GENERATED_BODY()

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	int DurationInSeconds;

	UPROPERTY(EditAnywhere)
	float DamagePerSecond;
};
