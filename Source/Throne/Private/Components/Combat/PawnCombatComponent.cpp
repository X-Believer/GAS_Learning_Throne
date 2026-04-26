// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/PawnCombatComponent.h"

#include "ThroneDebugHelper.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/ThroneWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister,
                                                 AThroneWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("Weapon with tag %s is already registered!"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponHitTargetActor);
	InWeaponToRegister->OnWeaponEndHitTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponEndHitTargetActor);
	
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldToggle, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AThroneWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		
		check(WeaponToToggle);
		
		if (bShouldToggle)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
	
	//TODO: Handle body collision boxes
}

void UPawnCombatComponent::OnWeaponHitTargetActor(AActor* OtherActor)
{
}

void UPawnCombatComponent::OnWeaponEndHitTargetActor(AActor* OtherActor)
{
}
