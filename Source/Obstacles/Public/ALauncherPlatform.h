// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APlatform.h"
#include "ALauncherPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLES_API AALauncherPlatform : public AAPlatform
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FVector TargetVector;
};
