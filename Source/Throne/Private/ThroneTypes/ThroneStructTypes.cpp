// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneTypes/ThroneStructTypes.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"

bool FThroneHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant != nullptr;
}
