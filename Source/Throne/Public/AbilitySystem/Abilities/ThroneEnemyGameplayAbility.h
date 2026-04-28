// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ThroneGameplayAbility.h"
#include "ThroneEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AThroneEnemyCharacter;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneEnemyGameplayAbility : public UThroneGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Throne|Ability")
	AThroneEnemyCharacter* GetEnemyCharacterFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Throne|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Throne|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(const TSubclassOf<UGameplayEffect> DamageEffect, const FScalableFloat& InDamageScalableFloat) const;
	
private:
	TWeakObjectPtr<AThroneEnemyCharacter> CachedEnemyCharacter;
};
