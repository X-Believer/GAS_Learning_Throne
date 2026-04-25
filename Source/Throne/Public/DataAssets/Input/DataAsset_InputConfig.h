// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct FThroneInputActionConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction != nullptr;
	}
};
/**
 * 
 */
UCLASS()
class THRONE_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FThroneInputActionConfig> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FThroneInputActionConfig> AbilityInputActions;
	
	UFUNCTION()
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};