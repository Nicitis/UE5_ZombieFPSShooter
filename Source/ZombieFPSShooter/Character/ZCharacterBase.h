// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EZMovementMode.h"
#include "ZCharacterBase.generated.h"

UCLASS()
class ZOMBIEFPSSHOOTER_API AZCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/* Movements */
public:
	UFUNCTION(BlueprintCallable, Category = Mover)
	virtual void StartCrouch();

	UFUNCTION(BlueprintCallable, Category = Mover)
	virtual void StopCrouch();

	UFUNCTION(BlueprintCallable, Category = Mover)
	virtual void StartSprint();

	UFUNCTION(BlueprintCallable, Category = Mover)
	virtual void StopSprint();

protected:
	void TryToStandUp();

/* Blueprint Events */
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnCrouched();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStandedUp();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMovedInput(float x, float y);

/* Properties for the character control. */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float StandHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float CrouchHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float BaseWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float CrouchSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float SprintSpeedMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bCrouchToggle : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bSprintToggle : 1;

	// If the player tries to stand up in a crouch status, this flag will be enabled.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bWantsToStandUp : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	EZMovementMode MovementMode;
};
