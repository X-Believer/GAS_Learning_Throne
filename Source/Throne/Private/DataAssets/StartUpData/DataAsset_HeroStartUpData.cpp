// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"
#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"
#include "ThroneTypes/ThroneStructTypes.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UThroneAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel) const
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	for (const FThroneHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec((AbilitySet.AbilityToGrant.Get()));
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
