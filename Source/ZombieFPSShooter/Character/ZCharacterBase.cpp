// Fill out your copyright notice in the Description page of Project Settings.


#include "ZCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Collision.h"

// Sets default values
AZCharacterBase::AZCharacterBase()
	: CrouchHeight(56.0f)
	, StandHeight(96.0f)
	, BaseWalkSpeed(300.0f)
	, CrouchSpeedMultiplier(0.5f)
	, SprintSpeedMultiplier(1.5f)
	, bCrouchToggle(false)
	, bSprintToggle(false)
	, bWantsToStandUp(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AZCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// 디버그 메시지를 5초간 표시합니다.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We area using FPSCharacter"));

}

// Called every frame
void AZCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWantsToStandUp)
	{
		TryToStandUp();
	}
}

// Called to bind functionality to input
void AZCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/* Move/Control Section */
/// <summary>
/// 앉기를 시작합니다.
/// </summary>
void AZCharacterBase::StartCrouch()
{
	bCrouchToggle = true;

	if (MovementMode == EZMovementMode::Sprinting)
	{
		StopSprint();
	}

	if (!GetCharacterMovement()->IsFalling())
	{
		MovementMode = EZMovementMode::Crouching;
		bWantsToStandUp = false;

		OnCrouched();
	}
}

/// <summary>
/// 앉기를 중단합니다. 일어설 수 있는지를 확인해 일어섭니다.
/// </summary>
void AZCharacterBase::StopCrouch()
{
	bCrouchToggle = false;
	bWantsToStandUp = true;
}

/// <summary>
/// 달리기를 시작합니다.
/// </summary>
void AZCharacterBase::StartSprint()
{
	if (MovementMode == EZMovementMode::Walking)
	{
		MovementMode = EZMovementMode::Sprinting;
		GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed * SprintSpeedMultiplier;
	}
}

/// <summary>
/// 달리기를 중단합니다.
/// </summary>
void AZCharacterBase::StopSprint()
{
	if (MovementMode == EZMovementMode::Sprinting)
	{
		MovementMode = EZMovementMode::Walking;
		GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
}

/// <summary>
/// 앉은 상태에서 일어설 수 있는지 확인하고, 머리 위에 장애물이 없다면 일어섭니다.
/// </summary>
void AZCharacterBase::TryToStandUp()
{
	FHitResult OutHit;
	float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector TraceStart = GetActorLocation() + GetActorUpVector() * (CrouchHeight/* + CapsuleRadius*/);
	FVector TraceEnd = GetActorLocation() + GetActorUpVector() * (1.1f * StandHeight);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(CapsuleRadius);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore current actor.

	bool bHit = GetWorld()->SweepSingleByChannel(
		OutHit,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		QueryParams
	);

// 디버그 드로잉 (테스트용)
//#if WITH_EDITOR
//	DrawDebugSphere(GetWorld(), TraceStart, CapsuleRadius, 12, FColor::Green, false, 2.0f);
//	DrawDebugSphere(GetWorld(), TraceEnd, CapsuleRadius, 12, bHit ? FColor::Red : FColor::Green, false, 2.0f);
//	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Red : FColor::Green, false, 2.0f, 0, 2.0f);
//#endif

	if (!bHit)
	{
		MovementMode = EZMovementMode::Walking;
		bWantsToStandUp = false;
		OnStandedUp(); 
	}
}

