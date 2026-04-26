// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ThroneGameplayTags.h"
#include "Items/Weapons/ThroneHeroWeapon.h"

AThroneHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	return Cast<AThroneHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AThroneHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AThroneHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnWeaponHitTargetActor(AActor* OtherActor)
{
	if (OverlappedActors.Contains(OtherActor)) return;
	OverlappedActors.AddUnique(OtherActor);
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = OtherActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), 
		ThroneGameplayTags::Shared_Event_MeleeHit, 
		Data);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), 
		ThroneGameplayTags::PlayerTag_Event_HitPause, 
		FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponEndHitTargetActor(AActor* OtherActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(), 
		ThroneGameplayTags::PlayerTag_Event_HitPause, 
		FGameplayEventData());
}
