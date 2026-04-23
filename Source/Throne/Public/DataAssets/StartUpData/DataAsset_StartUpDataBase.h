// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UThroneAbilitySystemComponent;
class UThroneGameplayAbility;
/**
 * 
 */
UCLASS()
class THRONE_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UThroneAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UThroneGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UThroneGameplayAbility>> ReactiveAbilities;
	
	void GrantAbilities(const TArray<TSubclassOf<UThroneGameplayAbility>>& InAbilitiesToGive, UThroneAbilitySystemComponent* InThroneASCToGive, int32 ApplyLevel = 1) const;
};
