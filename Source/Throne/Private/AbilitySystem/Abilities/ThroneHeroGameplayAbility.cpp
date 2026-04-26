// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"

#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
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

FGameplayEffectSpecHandle UThroneHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> DamageEffect, float InWeaponBaseDamage, FGameplayTag AttackTypeTag, int32 InComboCount)
{
	check(DamageEffect);
	
	FGameplayEffectContextHandle ContextHandle = GetThroneAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetThroneAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		DamageEffect,
		GetAbilityLevel(),
		ContextHandle);
	
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		ThroneGameplayTags::Shared_SetByCaller_BaseDamage, 
		InWeaponBaseDamage);
	
	if (AttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
			AttackTypeTag, 
			InComboCount);
	}
	
	return EffectSpecHandle;
}
