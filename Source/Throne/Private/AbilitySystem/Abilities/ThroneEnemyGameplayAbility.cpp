// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/ThroneEnemyGameplayAbility.h"

#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
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

FGameplayEffectSpecHandle UThroneEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	const TSubclassOf<UGameplayEffect> DamageEffect, const FScalableFloat& InDamageScalableFloat) const
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
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	
	return EffectSpecHandle;
}
