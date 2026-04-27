// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/Weapons/ThroneWeaponBase.h"
#include "ThroneTypes/ThroneStructTypes.h"
#include "ThroneHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API AThroneHeroWeapon : public AThroneWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FThroneHeroWeaponData HeroWeaponData;
	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
