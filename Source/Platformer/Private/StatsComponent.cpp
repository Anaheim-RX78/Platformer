// © 2024 Anaheim-RX78. All rights reserved.

#include "StatsComponent.h"

UStatsComponent::UStatsComponent() {
	this->PrimaryComponentTick.bCanEverTick = true;
}


void UStatsComponent::BeginPlay() {
	Super::BeginPlay();
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UStatsComponent::IncreaseDistanceMoved(const float DeltaDistance) {
	this->TotalDistanceMoved += DeltaDistance;
	GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Distance moved: %.2f"), this->TotalDistanceMoved));
}

void UStatsComponent::ReduceHealth(const int DeltaHealth) {
	this->Health -= DeltaHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health reduced by %d"), DeltaHealth));
}

void UStatsComponent::ResetHealth() {
	this->Health = 0;
	this->DeathCount++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Health reset to 0"));
}

void UStatsComponent::IncreaseJumpCount() {
	this->JumpCount++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Jump count increased to %d"), this->JumpCount));
}
