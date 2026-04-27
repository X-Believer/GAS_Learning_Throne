// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "ThroneStructTypes.generated.h"

class UThroneHeroGameplayAbility;
class UInputMappingContext;
class UThroneHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FThroneHeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UThroneHeroGameplayAbility> AbilityToGrant;
	
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FThroneHeroWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UThroneHeroLinkedAnimLayer> WeaponAniLayerToLink;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FThroneHeroAbilitySet> DefaultWeaponAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};
