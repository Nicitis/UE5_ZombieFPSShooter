// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPSSHOOTER_API AZGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AZGameMode();

	virtual void BeginPlay() override;

private:
};
