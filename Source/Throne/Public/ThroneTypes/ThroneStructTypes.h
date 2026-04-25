// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once
#include "GameplayTagContainer.h"
#include "ThroneStructTypes.generated.h"

class UInputMappingContext;
class UThroneGameplayAbility;
class UThroneHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FThroneHeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UThroneGameplayAbility> AbilityToGrant;
	
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
};
