// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UThroneEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class THRONE_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UThroneAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UThroneEnemyGameplayAbility>> EnemyStartUpAbilities;
};
