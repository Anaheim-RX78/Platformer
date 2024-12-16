// Fill out your copyright notice in the Description page of Project Settings.


#include "AMovingPlatform.h"

void AAMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetActorLocation();
	TargetPosition = GetActorLocation() + DeltaMovement;
}

void AAMovingPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime * Speed;
	const float t = 0.5f - 0.5f * FMath::Cos(Time);

	SetActorLocation(FMath::Lerp(InitialPosition, TargetPosition, t));
}
