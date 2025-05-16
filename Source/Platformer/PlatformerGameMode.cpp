// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerGameMode.h"
#include "PlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformerGameMode::APlatformerGameMode() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
