// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ThroneTypes/ThroneEnumTypes.h"
#include "ThroneGameplayAbility.generated.h"

class UThroneAbilitySystemComponent;
class UPawnCombatComponent;

UENUM()
enum class EThroneAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class THRONE_API UThroneGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility interface
	
	UPROPERTY(EditDefaultsOnly, Category="Throne|Ability")
	EThroneAbilityActivationPolicy AbilityActivationPolicy = EThroneAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	UThroneAbilitySystemComponent* GetThroneAbilitySystemComponentFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle) const;
	
	UFUNCTION(BlueprintCallable, Category="Throne|Ability", meta=(DisplayName="ApplyGameplayEffectSpecHandleToTarget",ExpandEnumAsExecs="SuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle, EThroneSuccessType& SuccessType);
};
