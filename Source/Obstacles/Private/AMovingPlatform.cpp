// Fill out your copyright notice in the Description page of Project Settings.


#include "AMovingPlatform.h"

void AAMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	this->InitialPosition = this->GetActorLocation();
	this->TargetPosition = this->GetActorLocation() + this->DeltaMovement;
}

void AAMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (this->HasAuthority()) {
		// If I'm the server, move the platform.
		this->MovePlatform(DeltaTime);
	} else {
		// If I'm not the server, request the server to move the platform.
		this->ServerMovePlatform(DeltaTime);
	}
}

void AAMovingPlatform::MovePlatform(float DeltaTime) {
	this->Time += DeltaTime * this->Speed;
	const float t = 0.5f - 0.5f * FMath::Cos(this->Time);

	this->SetActorLocation(FMath::Lerp(this->InitialPosition, this->TargetPosition, t));
}

void AAMovingPlatform::ServerMovePlatform_Implementation(float DeltaTime) {
	this->MovePlatform(DeltaTime);
}
