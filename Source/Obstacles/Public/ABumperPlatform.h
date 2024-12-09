// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AMovingPlatform.h"
#include "ABumperPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AABumperPlatform : public AAMovingPlatform
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	UPROPERTY(EditAnywhere)
	FVector BumperTargetPosition;
};
