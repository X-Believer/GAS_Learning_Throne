// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/ThroneAbilitySystemComponent.h"

#include "ThroneGameplayTags.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"
#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"
#include "ThroneTypes/ThroneStructTypes.h"

void UThroneAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		if (InInputTag.MatchesTag(ThroneGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			 TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UThroneAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(ThroneGameplayTags::InputTag_MustBeHeld)) return;
	
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InInputTag) || !Spec.IsActive()) continue;
		
		CancelAbilityHandle(Spec.Handle);
	}
}

void UThroneAbilitySystemComponent::OnAbilityInputHeld(const FGameplayTag& InInputTag)
{
}

void UThroneAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FThroneHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FWarriorHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilityHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;
	
	for (const FThroneHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec((AbilitySet.AbilityToGrant.Get()));
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilityHandles.AddUnique(GiveAbility(AbilitySpec));
	}
		
	if (InSpecialWeaponAbilities.IsEmpty()) return;
	
	for (const FWarriorHeroSpecialAbilitySet& SpecialAbilitySet : InSpecialWeaponAbilities)
	{
		if (!SpecialAbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec((SpecialAbilitySet.AbilityToGrant.Get()));
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(SpecialAbilitySet.InputTag);
		
		OutGrantedAbilityHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UThroneAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;
	
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (!SpecHandle.IsValid()) continue;
		ClearAbility(SpecHandle);
	}
	
	InSpecHandlesToRemove.Empty();
}

bool UThroneAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag InAbilityTag)
{
	check(InAbilityTag.IsValid());
	
	TArray<FGameplayAbilitySpec*> MatchingAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(InAbilityTag.GetSingleTagContainer(), MatchingAbilitySpecs);
	
	if (!MatchingAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, MatchingAbilitySpecs.Num() - 1);
		const FGameplayAbilitySpec* SpecToActivate = MatchingAbilitySpecs[RandomAbilityIndex];
		
		check(SpecToActivate);
		
		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	
	return false;
}
