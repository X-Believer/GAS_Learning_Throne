// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ThroneTypes/ThroneEnumTypes.h"
#include "ThroneSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API UThroneSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EThroneGameDifficulty SavedCurrentGameDifficulty;
};
