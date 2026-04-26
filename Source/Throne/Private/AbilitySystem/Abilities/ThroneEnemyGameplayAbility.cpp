// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/ThroneEnemyGameplayAbility.h"

#include "Characters/ThroneEnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"

AThroneEnemyCharacter* UThroneEnemyGameplayAbility::GetEnemyCharacterFromActorInfo() const
{
	if (!CachedEnemyCharacter.IsValid())
	{
		return Cast<AThroneEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UThroneEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo() const
{
	return Cast<UEnemyCombatComponent>(GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent());
}
