// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPSSHOOTER_API UZAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UZAnimInstance();
	
// Section. Native Methods
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

// Properties
protected:
	// 데이터 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// 이동 벡터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	// 현재 속력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	// 이동 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	// 이동 최소 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshold;

	// 공중에 있는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	// 점프 중인지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	// 점프 기준 최소 수직 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshold;

	// 달리기 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsRunning : 1;

	// 달리기 기준 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float RunningThreshold;
};
