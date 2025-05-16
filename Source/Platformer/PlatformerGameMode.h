// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

UCLASS(minimalapi)
class APlatformerGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	/**
	 * Constructor for APlatformerGameMode class.
	 * Initializes the default pawn class to a specific blueprint character if available.
	 *
	 * @return An instance of the APlatformerGameMode class.
	 */
	APlatformerGameMode();
};
