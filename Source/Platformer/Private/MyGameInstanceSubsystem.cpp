// © 2024 Anaheim-RX78. All rights reserved.

#include "MyGameInstanceSubsystem.h"

void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("MyGameInstanceSubsystem Initialized"));
}

void UMyGameInstanceSubsystem::Deinitialize() {
	Super::Deinitialize();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("MyGameInstanceSubsystem Deinitialized"));
}

void UMyGameInstanceSubsystem::IncreaseTimeElapsed(const float DeltaTime) {
	this->TimeElapsed += DeltaTime;
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Time Elapsed: %.2f"), this->TimeElapsed));
}

void UMyGameInstanceSubsystem::IncreaseDeathCount() {
	this->TotalDeathCount++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Total Death Count: %d"), this->TotalDeathCount));
}
