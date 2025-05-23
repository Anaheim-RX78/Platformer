// © 2024 Anaheim-RX78. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Coin.generated.h"

UCLASS()
class PLATFORMER_API ACoin : public AActor {
	GENERATED_BODY()

public:
	/**
	 * Default constructor for the ACoin class. This constructor initializes the coin's components,
	 * sets up collision responses, and binds the overlap event for interaction with other actors.
	 *
	 * @return An instance of ACoin with default values and initial setup.
	 */
	ACoin();

protected:
	/**
	 * Initializes the coin's position and target movement offset. This method is called when the game
	 * starts or when the actor is spawned, setting up the initial and target positions of the coin
	 * based on its current location and predefined movement delta.
	 */
	virtual void BeginPlay() override;

	/**
	 * Represents the static mesh component of the coin. This component serves as the visual representation of the coin
	 * and is used to define its appearance on the screen. It also handles collision responses with visibility
	 * and pawn channels, and is bound to the overlap event for interacting with other actors.
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * Represents the capsule component of the actor. This component is primarily used for handling
	 * collision detection, such as overlap events or interactions with other actors in the game.
	 * It defines the shape and size of the collision area associated with the actor.
	 */
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;

	/**
	 * Handles the overlap event triggered when another actor intersects with the coin's collision component.
	 * This function checks if the overlapping actor is a platformer character, increments the character's coin count,
	 * optionally plays a sound effect, and triggers the coin's disappearance.
	 *
	 * @param OverlappedComponent The component of the coin that was overlapped.
	 * @param OtherActor The actor that triggered the overlap event.
	 * @param OtherComp The specific component of the overlapping actor that caused the overlap.
	 * @param OtherBodyIndex The index of the overlapping actor's body that triggered the event (used in multi-body scenarios).
	 * @param bFromSweep Indicates whether the overlap event was triggered from a sweeping movement.
	 * @param SweepResult Detailed information about the sweep that triggered the overlap, including impact data.
	 */
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Represents the movement speed of the coin during its update cycle. This value is used
	 * as a multiplier to control how quickly the coin moves between its initial and target positions
	 * over time. A higher value results in faster motion, while a lower value slows it down.
	 */
	UPROPERTY(EditAnywhere)
	float Speed = 1;

	/**
	 * Represents the initial position of the coin in the game world. This vector is set
	 * during the actor's initialization (e.g., in BeginPlay) to store the starting location
	 * of the coin. It serves as a reference point for calculating movement interpolations
	 * or animations between the initial and target positions.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	/**
	 * Represents the offset by which the coin's target position is calculated relative to its initial position.
	 * This vector determines the movement range of the coin and is added to the initial position to set
	 * the target position during the coin's setup or initialization.
	 */
	UPROPERTY(EditAnywhere)
	FVector DeltaMovement;

	/**
	 * Represents the target position of the coin in the game world. This vector is calculated during
	 * the actor's initialization and is used to define the destination point for the coin's movement.
	 * The target position is determined by adding the predefined movement offset (DeltaMovement)
	 * to the coin's initial position and is utilized in interpolating the coin's motion.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	/**
	 * Represents the time elapsed or used for driving time-based updates or animations within the game.
	 * This property can be utilized as a variable for controlling or tracking behaviors dependent
	 * on temporal dynamics, such as movement interpolation or animations.
	 */
	UPROPERTY(VisibleAnywhere)
	float Time = 0;

	/**
	 * A sound cue object used to define the audio effect associated with a specific action or event.
	 * This variable can be edited in the editor and accessed in Blueprints for customization.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* SoundEffect;

	/**
	 * Blueprint-implementable event to handle the disappearance of the object.
	 * This function can be overridden in Blueprints to define specific behavior
	 * when the object needs to disappear from the scene.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void Disappear();

public:
	/**
	 * Updates the state and position of the coin based on DeltaTime. This method calculates
	 * the current position of the coin by interpolating between its initial and target positions
	 * using a sinusoidal motion pattern.
	 *
	 * @param DeltaTime The time elapsed since the last frame, used to update the coin's movement
	 * and animation.
	 */
	virtual void Tick(float DeltaTime) override;
};
