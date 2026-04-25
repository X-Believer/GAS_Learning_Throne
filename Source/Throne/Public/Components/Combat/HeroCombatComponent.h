// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AThroneHeroWeapon;
/**
 * 
 */
UCLASS()
class THRONE_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Throne|Combat")
	AThroneHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
