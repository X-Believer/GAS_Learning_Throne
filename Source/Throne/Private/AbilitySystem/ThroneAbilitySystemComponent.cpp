// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/ThroneAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"
#include "ThroneTypes/ThroneStructTypes.h"

void UThroneAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UThroneAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UThroneAbilitySystemComponent::OnAbilityInputHeld(const FGameplayTag& InInputTag)
{
}

void UThroneAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FThroneHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilityHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;
	
	for (const FThroneHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilityHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}
