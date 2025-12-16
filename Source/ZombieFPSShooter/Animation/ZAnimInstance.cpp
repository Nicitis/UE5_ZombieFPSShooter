// Fill out your copyright notice in the Description page of Project Settings.


#include "ZAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UZAnimInstance::UZAnimInstance()
{
	MovingThreshold = 3.0f;
	JumpingThreshold = 100.f;
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
}

