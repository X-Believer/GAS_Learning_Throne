// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UThroneGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (AbilityActivationPolicy == EThroneAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
		}
	}
}

void UThroneGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (AbilityActivationPolicy == EThroneAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UThroneGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UThroneAbilitySystemComponent* UThroneGameplayAbility::GetThroneAbilitySystemComponentFromActorInfo() const
{
	return Cast<UThroneAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UThroneGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle) const
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	check(TargetASC && InSpecHandle.IsValid());
	
	return GetThroneAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data, 
		TargetASC);
}

FActiveGameplayEffectHandle UThroneGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle, EThroneSuccessType& SuccessType)
{
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(Target, InSpecHandle);
	SuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EThroneSuccessType::Success : EThroneSuccessType::Failure;
	return ActiveGameplayEffectHandle;
}
