// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ADamagePlatform.h"
#include "AMovingPlatform.h"
#include "AVoidPlatform.generated.h"

UCLASS()
class OBSTACLES_API AAVoidPlatform : public AAMovingPlatform {
	GENERATED_BODY()

	/**
	 * Default constructor for the AAVoidPlatform class.
	 * Initializes the AAVoidPlatform instance by calling the base class constructor (AAMovingPlatform)
	 * and sets up collision responses for the platform's mesh component to handle visibility and pawn channels.
	 *
	 * @return A new instance of the AAVoidPlatform class.
	 */
	AAVoidPlatform();

	/**
	 * Handles the event when another actor begins overlapping with the platform.
	 * If the platform is enabled, it checks whether the overlapping actor is a platformer character.
	 * If valid, it plays a sound and applies void-type damage to the character.
	 *
	 * @param OverlappedComponent The component of the platform that is being overlapped.
	 * @param OtherActor The actor that initiated the overlap.
	 * @param OtherComp The specific component of the other actor involved in the overlap.
	 * @param OtherBodyIndex The index of the body for the overlapping component.
	 * @param bFromSweep Whether the overlap occurred due to a sweep operation.
	 * @param SweepResult The hit result data from the sweep that caused the overlap, containing impact details.
	 */
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
