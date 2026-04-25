// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/ThroneHeroWeapon.h"

AThroneHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	return Cast<AThroneHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
