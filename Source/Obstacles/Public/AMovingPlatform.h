// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APlatform.h"
#include "AMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AAMovingPlatform : public AAPlatform
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	float Speed = 1;

	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	UPROPERTY(EditAnywhere)
	FVector DeltaMovement;

	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	UPROPERTY(VisibleAnywhere)
	float Time = 0;
};
