// Fill out your copyright notice in the Description page of Project Settings.


#include "ZGameMode.h"

AZGameMode::AZGameMode() : AGameModeBase()
{
	// Set default pawn class to our player.
	static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_ZCharacterBase.BP_ZCharacterBase_C'"));
	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ZombieFPSShooter.ZPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void AZGameMode::BeginPlay()
{
}
