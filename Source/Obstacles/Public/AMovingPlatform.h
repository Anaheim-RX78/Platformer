// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APlatform.h"
#include "AMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AAMovingPlatform : public AAPlatform {
	GENERATED_BODY()

protected:
	/**
	 * Called when the game starts or when the actor is spawned.
	 *
	 * Overrides the BeginPlay method of the parent class to perform
	 * initial setup for the moving platform. Specifically, it sets
	 * the initial position of the platform and calculates the target
	 * position based on the initial location and DeltaMovement property.
	 *
	 * This initialization step ensures that the platform has its
	 * required position information established before the game
	 * begins updating the actor during the Tick phase.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * Called every frame to update the actor's behavior.
	 *
	 * Overrides the Tick method of the parent class to handle
	 * the continuous movement of the platform. The method calculates
	 * a smooth oscillating movement using a cosine function. The position
	 * of the platform is interpolated between its initial position and a
	 * target position using a time-based parameter influenced by the platform's Speed.
	 *
	 * @param DeltaTime The time elapsed since the last frame, used to ensure
	 *                  movement calculations are frame-rate independent.
	 */
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * The speed multiplier controlling the rate of movement for the platform.
	 *
	 * This variable influences how quickly the platform progresses
	 * through its movement cycle, which interpolates its position
	 * between the InitialPosition and the TargetPosition. Higher values
	 * result in faster movement, while lower values slow it down.
	 * It is editable in the editor, allowing for dynamic adjustments
	 * during level design.
	 */
	UPROPERTY(EditAnywhere)
	float Speed = 1;

	/**
	 * Stores the initial position of the platform when the game begins.
	 *
	 * This variable is used to define the starting location of the platform
	 * in the game world. It is initialized during the BeginPlay method by
	 * capturing the actor's position at the start of the game. The value
	 * of this variable is essential for defining the bounds of the platform's
	 * movement, as it is used in conjunction with the DeltaMovement property
	 * to compute the TargetPosition and facilitate smooth interpolation
	 * between its starting and target locations.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	/**
	 * Determines the offset used to calculate the target position for the platform's movement.
	 *
	 * This variable defines the relative displacement added to the platform's
	 * initial location to compute its target position. The platform oscillates
	 * between its InitialPosition and TargetPosition, which is derived by adding
	 * this DeltaMovement value to the initial location. It allows for customization
	 * of the platform's movement bounds and direction in the game world.
	 *
	 * The property is editable in the editor, enabling dynamic configuration
	 * during level design to achieve the desired movement range of the platform.
	 */
	UPROPERTY(EditAnywhere)
	FVector DeltaMovement;

	/**
	 * Represents the target position of the platform in the game world.
	 *
	 * This variable defines the destination location of the platform,
	 * which is calculated during the BeginPlay phase by adding the
	 * DeltaMovement to the InitialPosition. The platform interpolates
	 * between the InitialPosition and TargetPosition for smooth
	 * oscillatory movement during gameplay. It is updated every frame
	 * in the Tick method to determine the current position of the platform
	 * based on the interpolation factor influenced by Speed and DeltaTime.
	 *
	 * The value of TargetPosition is dynamically set during initialization
	 * and is crucial for defining the movement bounds of the platform.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	/**
	 * Tracks the elapsed time for the movement cycle of the platform.
	 *
	 * This variable accumulates time as the game progresses, updated
	 * every frame in the Tick method. It is scaled by the Speed property
	 * to determine the progression through the platform's oscillatory
	 * movement. The accumulated time is used in a cosine-based calculation
	 * to interpolate between InitialPosition and TargetPosition, resulting
	 * in smooth, periodic motion.
	 */
	UPROPERTY(VisibleAnywhere)
	float Time = 0;
};
