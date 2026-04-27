// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ThroneAbilitySystemComponent.generated.h"

struct FThroneHeroAbilitySet;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	void OnAbilityInputHeld(const FGameplayTag& InInputTag);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Ability", meta=(ApplyLevel="1"))
	void GrantHeroWeaponAbilities(const TArray<FThroneHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilityHandles);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};
