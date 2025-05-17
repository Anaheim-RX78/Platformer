// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstanceSubsystem.h"
#include "StatsComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlatformerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APlatformerCharacter : public ACharacter {
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY()
	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

	FVector PreviousLocation;

	float TotalDistanceMoved = 0.0f;

	int Health = 100;

	int JumpCount = 0;

	int DeathCount = 0;

public:
	APlatformerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsPoisoned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PoisonDurationInSeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsWin = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Coins = 0;

	UPROPERTY(BlueprintReadOnly)
	UStatsComponent* Stats;

	void GetDamage(int Damage);

	void IncreaseDistanceMoved(float DeltaDistance);

	void ReduceHealth(int DeltaHealth);

	UFUNCTION(BlueprintCallable)
	int GetHealth() const {
		return this->Health;
	}

	void ResetHealth();

	void IncreaseJumpCount();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void JumpAndIncreaseCounter(const FInputActionValue& Value);

	// To add mapping context
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {
		return CameraBoom;
	}

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const {
		return FollowCamera;
	}

	virtual void Tick(float DeltaSeconds) override;
};
