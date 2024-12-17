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
class OBSTACLES_API AATrapPlatform : public AAMovingPlatform
{
	GENERATED_BODY()

	AATrapPlatform();

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Trap;
};
