// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ThroneEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UThroneAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel) const
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	if (!EnemyStartUpAbilities.IsEmpty())
	{
		for (const TSubclassOf<UThroneEnemyGameplayAbility>& Ability : EnemyStartUpAbilities)
		{
			if (!Ability) continue;
			FGameplayAbilitySpec AbilitySpec(Ability);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
