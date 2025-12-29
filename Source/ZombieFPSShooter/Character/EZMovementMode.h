#pragma once

#include "CoreMinimal.h"
#include "EZMovementMode.generated.h"

/**
 * Custom enum for character's finite movement states.
 */
UENUM(BlueprintType)
enum class EZMovementMode : uint8
{
	Walking		UMETA(DisplayName = "Walking Mode"),
	Sprinting	UMETA(DisplayName = "Sprinting Mode"),
	Crouching	UMETA(DisplayName = "Crouching Mode"),
	EditMode	UMETA(DisplayName = "Edit Mode"),

	Count		UMETA(Hidden)
};