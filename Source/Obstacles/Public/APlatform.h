// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Platformer/PlatformerCharacter.h"
#include "APlatform.generated.h"

UCLASS()
class OBSTACLES_API AAPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	static void GetDamage(APlatformerCharacter* Character, int Damage);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
