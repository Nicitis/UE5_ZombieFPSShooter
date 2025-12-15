// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZCharacterBase.h"
#include "ZCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPSSHOOTER_API AZCharacterPlayer : public AZCharacterBase
{
	GENERATED_BODY()

public:
	AZCharacterPlayer();
	
protected:
	virtual void BeginPlay() override;

/* Input Section */
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void InitializeCharacterControl();
	
/* Move/Control Section */
private:
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void StartJump();
	void StopJump();

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FPSCameraComponent;
};
