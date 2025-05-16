// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AMovingPlatform.h"
#include "APoisonPlatform.generated.h"

UCLASS()
class OBSTACLES_API AAPoisonPlatform : public AAMovingPlatform {
	GENERATED_BODY()

protected:
	/**
	 * Handles the event when another actor begins overlapping with this platform.
	 * If the platform is enabled and a valid character overlaps, it plays a sound
	 * and applies poison damage to the character.
	 *
	 * @param OverlappedComponent The component on this platform that was overlapped.
	 * @param OtherActor The actor that initiated the overlap.
	 * @param OtherComp The specific component of the other actor involved in the overlap.
	 * @param OtherBodyIndex The body index associated with the component of the overlapping actor.
	 * @param bFromSweep Specifies whether the overlap happened as a result of a sweep operation.
	 * @param SweepResult Provides details about the sweep, if applicable (impact point, normal, etc.).
	 */
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	/**
	 * Specifies the duration in seconds for which the platform will remain active or apply its effect.
	 * This property is editable in the editor and can be configured to control the platform's behavior.
	 */
	UPROPERTY(EditAnywhere)
	int DurationInSeconds;

	/**
	 * Determines the amount of poison damage applied per second to overlapping actors.
	 * This value defines how much damage will be inflicted continuously as long as an actor
	 * remains in contact with this platform.
	 */
	UPROPERTY(EditAnywhere)
	float DamagePerSecond;
};
