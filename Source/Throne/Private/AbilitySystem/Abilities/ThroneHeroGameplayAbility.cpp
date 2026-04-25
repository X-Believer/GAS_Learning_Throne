// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"

#include "Characters/ThroneHeroCharacter.h"
#include "Controllers/ThroneHeroController.h"

AThroneHeroCharacter* UThroneHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<AThroneHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AThroneHeroController* UThroneHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<AThroneHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UThroneHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
