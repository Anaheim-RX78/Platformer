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
	UPROPERTY(EditAnywhere)
	bool IsRecurrent;

	UPROPERTY(EditAnywhere)
	int DurationInSeconds;

	UPROPERTY(EditAnywhere)
	float DamagePerSecond;
};
