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

	AABumperPlatform();

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Balloon;
};
