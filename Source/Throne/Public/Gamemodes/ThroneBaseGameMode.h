// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThroneTypes/ThroneEnumTypes.h"
#include "ThroneBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API AThroneBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThroneBaseGameMode();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settigns")
	EThroneGameDifficulty CurrentGameDifficulty = EThroneGameDifficulty::Medium;
	
public:
	FORCEINLINE EThroneGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
