// © 2024 Anaheim-RX78. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLATFORMER_API UStatsComponent : public UActorComponent {
	GENERATED_BODY()

public:
	/**
	 * @brief Constructs and initializes the UStatsComponent instance.
	 *
	 * This constructor sets up the initial state of the UStatsComponent class,
	 * enabling the component to tick every frame during gameplay. It ensures
	 * the component is prepared for use within the Unreal Engine framework.
	 *
	 * @return A newly initialized instance of UStatsComponent.
	 */
	UStatsComponent();

protected:
	virtual void BeginPlay() override;

	/**
 * @brief Tracks the total distance moved by the player.
 *
 * This variable accumulates the total distance the player has traveled during gameplay.
 * It starts at 0.0 and increases as the player moves, providing a measure of the overall
 * movement within the game world.
 */
	float TotalDistanceMoved = 0.0f;

	/**
	 * @brief Represents the player's current health value.
	 *
	 * This variable stores the player's health, initially set to 100. It is used
	 * to track the player's remaining health during gameplay and can be modified
	 * through various in-game actions, such as taking damage or healing.
	 */
	int Health = 100;

	/**
	 * @brief Tracks the number of jumps performed by the player.
	 *
	 * This variable is incremented each time the player executes a jump action.
	 * It is used to monitor the player's jump activity during gameplay and may
	 * assist in debugging, analytics, or gameplay mechanics.
	 */
	int JumpCount = 0;

	/**
	 * @brief Tracks the number of times the player's health has been reset.
	 *
	 * This variable is incremented each time the player runs out of health
	 * and triggers the ResetHealth function. It serves as a statistic for
	 * monitoring player deaths during gameplay and can be used for metrics
	 * or gameplay logic.
	 */
	int DeathCount = 0;

public:
	/**
	 * @brief Updates the component every frame.
	 *
	 * This method is called every frame during gameplay to update the stats component.
	 * It allows the component to perform regular updates based on the elapsed time or
	 * game events.
	 *
	 * @param DeltaTime The time elapsed since the last frame, in seconds.
	 * @param TickType Specifies the type of tick the component should process.
	 * @param ThisTickFunction Provides context for the tick, enabling additional functionality.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

		/**
	 * @brief Increases the total distance moved by the player by a specified amount.
	 *
	 * This method adds the specified value to the player's total distance moved
	 * and displays an on-screen debug message showing the new total distance.
	 * It is useful for tracking player movement during gameplay.
	 *
	 * @param DeltaDistance The amount of distance to add to the player's total distance moved.
	 */
	void IncreaseDistanceMoved(float DeltaDistance);

	/**
	 * @brief Reduces the player's current health by a specified amount.
	 *
	 * This method deducts a specified amount from the player's current health
	 * and displays an on-screen debug message indicating the amount by which
	 * the health has been reduced. It is useful for managing damage effects
	 * or simulating player health loss during gameplay.
	 *
	 * @param DeltaHealth The amount of health to subtract from the player's current health.
	 */
	void ReduceHealth(int DeltaHealth);

	/**
	 * @brief Retrieves the current health value of the player.
	 *
	 * This method returns the player's current health value, which is stored
	 * as an integer. It is useful for obtaining the player's health status
	 * for gameplay logic or UI display.
	 *
	 * @return The current health value of the player.
	 */
	UFUNCTION(BlueprintCallable)
	int GetHealth() const {
		return this->Health;
	}

	/**
	 * @brief Resets the player's health to zero and updates related statistics.
	 *
	 * This method sets the player's health to 0, increments the death count,
	 * and communicates with the game instance subsystem to update the global
	 * death count. Additionally, it displays a debug message on the screen
	 * indicating that the player's health has been reset.
	 */
	void ResetHealth();

	/**
	 * @brief Increments the player's jump count and displays the updated count on the screen.
	 *
	 * This method increases the JumpCount by 1 and uses the Unreal Engine debugging system to
	 * display the updated jump count as a message on the screen for debugging purposes.
	 */
	void IncreaseJumpCount();
};
