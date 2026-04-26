// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"
#include "ThroneHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AThroneHeroController;
class AThroneHeroCharacter;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneHeroGameplayAbility : public UThroneGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	AThroneHeroCharacter* GetHeroCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	AThroneHeroController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category="Throne|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> DamageEffect, float InWeaponBaseDamage, FGameplayTag AttackTypeTag, int32 InComboCount);
	
private:
	TWeakObjectPtr<AThroneHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AThroneHeroController> CachedHeroController;
};
