// Fill out your copyright notice in the Description page of Project Settings.


#include "ZAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UZAnimInstance::UZAnimInstance()
{
	MovingThreshold = 3.0f;
	JumpingThreshold = 100.0f;
	RunningThreshold = 10.0f;
}

void UZAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Owner를 획득하기 위해 GetOwningActor를 호출할 수 있다.
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UZAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// 업데이트 함수로, 여기에서 실제 필요한 값을 얻어온다.
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < bIsIdle;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (JumpingThreshold < Velocity.Z);
		bIsRunning = RunningThreshold <= GroundSpeed;
	}
}

