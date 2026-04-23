// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UThroneAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel) const
{
	check(InASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UThroneGameplayAbility>>& InAbilitiesToGive,
	UThroneAbilitySystemComponent* InAscToGive, int32 ApplyLevel) const
{
	if (InAscToGive == nullptr)
	{
		return;
	}
	
	for (const TSubclassOf<UThroneGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
