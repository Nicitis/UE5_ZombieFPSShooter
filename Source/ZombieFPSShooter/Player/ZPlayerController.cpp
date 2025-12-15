// Fill out your copyright notice in the Description page of Project Settings.


#include "ZPlayerController.h"

void AZPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
