// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Items/Weapons/ThroneHeroWeapon.h"

void AThroneHeroWeapon::AssignGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AThroneHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
