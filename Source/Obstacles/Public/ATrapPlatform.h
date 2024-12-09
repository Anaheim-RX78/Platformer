// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ADamagePlatform.h"
#include "AMovingPlatform.h"
#include "Components/BoxComponent.h"
#include "ATrapPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AATrapPlatform : public AADamagePlatform
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	bool IsTrapActive;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Trap;
};
