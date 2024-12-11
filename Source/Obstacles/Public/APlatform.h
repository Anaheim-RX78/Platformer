// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Platformer/PlatformerCharacter.h"
#include "Sound/SoundCue.h"
#include "APlatform.generated.h"

UCLASS()
class OBSTACLES_API AAPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAPlatform();

protected:
	enum class DamageTypes
	{
		Normal,
		Trap,
		Poison,
		Void
	};

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* DamageSoundEffect;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TakeDamage(APlatformerCharacter* Character, DamageTypes DamageType) const;

private:
	static int GetDamage(const APlatformerCharacter* Character, DamageTypes DamageType);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
