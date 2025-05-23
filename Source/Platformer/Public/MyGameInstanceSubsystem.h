// © 2024 Anaheim-RX78. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameInstanceSubsystem.generated.h"

UCLASS()
class PLATFORMER_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem {
	GENERATED_BODY()

	/**
	 * @brief Represents the total time duration tracked by the game instance subsystem.
	 *
	 * This variable stores the cumulative time, in seconds, that has elapsed since the
	 * game instance subsystem began tracking. It is primarily updated during gameplay
	 * to monitor the progression of time and may be accessed for debugging or analytics
	 * purposes.
	 */
	float TimeElapsed = 0.f;

	/**
	 * @brief Tracks the total number of deaths recorded in the game instance.
	 *
	 * This variable maintains a cumulative count of player or character deaths
	 * that have occurred during the gameplay session. It is updated incrementally
	 * and utilized for gameplay analytics or debugging purposes.
	 */
	int TotalDeathCount = 0;

public:
	/**
	 * @brief Initializes the game instance subsystem during startup.
	 *
	 * This method is invoked when the subsystem is being initialized as part of the game instance startup process.
	 * It prepares the subsystem for use, performs initial setup, and displays a debug message to indicate successful initialization.
	 *
	 * @param Collection A reference to the subsystem collection that this subsystem is being added to.
	 *                   Allows access to other registered subsystems during initialization.
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * @brief Cleans up resources and finalizes the subsystem upon deinitialization.
	 *
	 * This method is invoked when the game instance subsystem is being deinitialized.
	 * It removes any persistent setups or references and displays a debug message
	 * indicating that the subsystem has been deinitialized.
	 */
	virtual void Deinitialize() override;

	/**
	 * @brief Retrieves the total time elapsed tracked by the game instance subsystem.
	 *
	 * This method returns the value of the internal time elapsed counter, representing the total duration
	 * that has been tracked since the initialization of the game instance subsystem.
	 *
	 * @return The total elapsed time, in seconds.
	 */
	float GetTimeElapsed() const {
		return TimeElapsed;
	}

	/**
	 * @brief Increases the total time elapsed tracked by the game instance subsystem.
	 *
	 * This method adds the specified delta time to the internal time elapsed counter
	 * and displays the updated total on screen as a debug message, using red text color.
	 *
	 * @param DeltaTime The time increment to be added to the elapsed time, in seconds.
	 */
	void IncreaseTimeElapsed(float DeltaTime);

	/**
	 * @brief Increases the total death count tracked by the game instance subsystem.
	 *
	 * This method increments the internal death count counter for the game instance
	 * and displays the updated total on screen as a debug message, using red text color.
	 */
	void IncreaseDeathCount();
};
