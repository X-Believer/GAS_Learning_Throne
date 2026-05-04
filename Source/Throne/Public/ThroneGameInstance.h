// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "ThroneGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FThroneGameLevelSet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta=(Categories="GameData.Level"))
	FGameplayTag LevelTag;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;
	
	bool IsValid() const
	{
		return !Level.IsNull() && LevelTag.IsValid();
	}
};

/**
 * 
 */
UCLASS()
class THRONE_API UThroneGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
protected:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FThroneGameLevelSet> GameLevelSets;
	
public:
	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag LevelTag) const;
};
