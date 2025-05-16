// Fill out your copyright notice in the Description page of Project Settings.


#include "AMovingPlatform.h"

void AAMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	this->InitialPosition = this->GetActorLocation();
	this->TargetPosition = this->GetActorLocation() + this->DeltaMovement;
}

void AAMovingPlatform::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);

	this->Time += DeltaTime * this->Speed;
	const float t = 0.5f - 0.5f * FMath::Cos(this->Time);

	this->SetActorLocation(FMath::Lerp(this->InitialPosition, this->TargetPosition, t));
}
