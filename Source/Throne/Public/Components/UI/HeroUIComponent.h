// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconSlotDelegate, FGameplayTag, AbilityInputTag, TSoftObjectPtr<UMaterialInterface>, SoftAbilityIconMaterial);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityCooldownBeginDelegate, FGameplayTag, AbilityInputTag, float, TotalCooldownDuration, float, CooldownRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoneInteractedDelegate, bool, bShouldDisplayInputKey);

/**
 * 
 */
UCLASS()
class THRONE_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAbilityIconSlotDelegate OnAbilityIconSlotChanged;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAbilityCooldownBeginDelegate OnAbilityCooldownBegin;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStoneInteractedDelegate OnStoneInteracted;
};
