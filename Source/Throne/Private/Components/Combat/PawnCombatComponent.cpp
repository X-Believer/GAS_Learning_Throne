// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/PawnCombatComponent.h"

#include "ThroneDebugHelper.h"
#include "Items/Weapons/ThroneWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister,
                                                 AThroneWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("Weapon with tag %s is already registered!"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	
	const FString WeaponString = FString::Printf(TEXT("A weapon named: %ls has been registered using tag %ls"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}

AThroneWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTag) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTag)) 
	{
		if (AThroneWeaponBase* FoundWeapon = CharacterCarriedWeaponMap[InWeaponTag])
		{
			return FoundWeapon;
		}
	}
	
	return nullptr;
}

AThroneWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (CurrentEquippedWeaponTag.IsValid())
	{
		return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
	}
	
	return nullptr;
}
