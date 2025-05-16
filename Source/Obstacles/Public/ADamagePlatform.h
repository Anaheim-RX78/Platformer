// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AMovingPlatform.h"
#include "ADamagePlatform.generated.h"

UCLASS()
class OBSTACLES_API AADamagePlatform : public AAMovingPlatform {
	GENERATED_BODY()

	/**
	 * Handles the event triggered when another actor overlaps with this damage platform.
	 * Applies damage to overlapping characters if the platform is enabled.
	 *
	 * @param OverlappedComponent The component of this actor that was overlapped.
	 * @param OtherActor The other actor that triggered the overlap event.
	 * @param OtherComp The specific component on the other actor that overlapped this actor.
	 * @param OtherBodyIndex The index of the body on the other actor that triggered the overlap.
	 * @param bFromSweep Whether the overlap was the result of a sweeping movement.
	 * @param SweepResult Details about the sweep that caused the overlap, if applicable.
	 */
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
