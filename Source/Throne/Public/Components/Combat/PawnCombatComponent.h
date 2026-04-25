// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AThroneWeaponBase;
/**
 * 
 */
UCLASS()
class THRONE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	void RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister, AThroneWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	AThroneWeaponBase* GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	AThroneWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UPROPERTY(BlueprintReadWrite, Category = "Throne|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AThroneWeaponBase*> CharacterCarriedWeaponMap;
};
