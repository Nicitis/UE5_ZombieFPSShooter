// Fill out your copyright notice in the Description page of Project Settings.


#include "ZCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AZCharacterBase::AZCharacterBase()
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

}

// Called to bind functionality to input
void AZCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

