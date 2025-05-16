// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Platformer/PlatformerCharacter.h"
#include "Sound/SoundCue.h"
#include "APlatform.generated.h"

UCLASS()
class OBSTACLES_API AAPlatform : public AActor {
	GENERATED_BODY()

public:
	/**
	 * Handles platform functionality within the game, providing mechanisms for gameplay interactions such as damages, effects, and overlaps.
	 * This class is intended to be used as a base for implementing different types of platforms with varying behaviors and functionalities.
	 */
	AAPlatform();

protected:
	/**
	 * Enumerates the types of damages that a platform can inflict on characters.
	 * This enumeration is used to specify the nature of the damage dealt, allowing
	 * for specialized gameplay behavior based on the damage type.
	 */
	enum class EDamageTypes {
		Normal,
		Trap,
		Poison,
		Void
	};

	/**
	 * Executes initialization logic when the platform actor enters the game world.
	 * This method is automatically called during the startup phase of the game
	 * and prepares the platform for gameplay by invoking its parent class's BeginPlay
	 * functionality.
	 */
	virtual void BeginPlay() override;

	/**
	 * Determines whether the platform is active and capable of interacting with other game objects.
	 * When set to `true`, the platform is enabled and can execute behaviors such as causing damage or responding to overlaps.
	 * When set to `false`, the platform is disabled and its functionality is bypassed during gameplay.
	 */
	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;

	/**
	 * Represents the static mesh component used to visually display the platform in the game world.
	 * This component also serves as the root component for the platform actor, enabling attachment
	 * of other components such as collision boxes and trap meshes.
	 * It is configurable in the editor, allowing designers to customize the appearance of the platform.
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * Represents a collision box used to detect overlaps and trigger events related to the platform.
	 * The collision box is primarily used for gameplay interactions such as handling character triggers when they come into contact with the platform.
	 * It is attached to the platform's mesh component and configured to generate overlap events, enabling dynamic responses during gameplay.
	 */
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	/**
	 * Represents the sound effect that is played when the platform inflicts damage.
	 * This sound cue enhances the auditory feedback during gameplay, providing
	 * an indication of damage events such as traps or harmful interactions triggered by the platform.
	 * It can be customized via the editor or blueprints for tailored audio effects.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* DamageSoundEffect;

	/**
	 * Triggered when another actor or component begins to overlap with the platform's collision box.
	 * This method can be used to implement various gameplay behaviors depending on the overlapping entity.
	 *
	 * @param OverlappedComponent The component belonging to this platform that detected the overlap.
	 * @param OtherActor The actor that overlaps with the platform.
	 * @param OtherComp The specific component of the overlapping actor that triggered the overlap event.
	 * @param OtherBodyIndex The index of the overlapping body, used for identifying specific parts of complex actors.
	 * @param bFromSweep Indicates whether the overlap was detected as a result of a sweeping movement.
	 * @param SweepResult Provides additional information about the overlap, such as impact point and normal.
	 */
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Plays a specified sound effect at a given start time, providing auditory feedback during gameplay interactions.
	 * This method is typically used to signal specific actions, such as damage being inflicted by the platform.
	 * The sound effect is only played if it has been assigned to the DamageSoundEffect property.
	 *
	 * @param StartTime The time in seconds at which the sound effect should start playing.
	 */
	void PlaySound(float StartTime) const;

	/**
	 * Inflicts damage on the specified character based on the given damage type. This calculates the appropriate
	 * damage value and modifies the character's health accordingly. If the damage exceeds or equals the character's
	 * current health, it resets their health.
	 *
	 * @param Character The character instance on which the damage will be inflicted.
	 * @param DamageType The type of damage being applied, determining how the damage is calculated.
	 */
	void MakeDamage(APlatformerCharacter* Character, EDamageTypes DamageType) const;

private:
	/**
	 * Calculates and returns the damage to be inflicted on a character based on the specified damage type.
	 * Adjusts damage properties or effects specific to certain damage types.
	 *
	 * @param Character The character that will receive the damage. Certain damage types may interact with this character context to apply additional attributes.
	 * @param DamageType The type of damage to be applied. This determines the behavior and value of the damage calculation.
	 * @return The calculated damage value as an integer. May return 0 if no damage is to be applied or the damage type is unrecognized.
	 */
	static int GetDamage(APlatformerCharacter* Character, EDamageTypes DamageType);

public:
	/**
	 * Updates the platform's state every frame based on the elapsed time since the last tick.
	 * This method facilitates dynamic behaviors that evolve or respond over time within the game's runtime.
	 *
	 * @param DeltaTime The time span in seconds since the last frame update, used for calculating frame-dependent operations.
	 */
	virtual void Tick(float DeltaTime) override;
};
