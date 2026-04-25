// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "ThroneInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API UThroneInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc, CallbackFunc InputHeldFunc);
};

template <class UserObject, typename CallbackFunc>
inline void UThroneInputComponent::BindNativeAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig,TEXT("InputConfig is null!"));
	
	if (UInputAction* InputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(InputAction, InTriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
inline void UThroneInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
	UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc,
	CallbackFunc InputHeldFunc)
{
	checkf(InInputConfig,TEXT("InputConfig is null!"));
	for (const FThroneInputActionConfig& Config : InInputConfig->AbilityInputActions)
	{
		if (!Config.IsValid()) continue;
		BindAction(Config.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, Config.InputTag);		
		BindAction(Config.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, Config.InputTag);
		BindAction(Config.InputAction, ETriggerEvent::Triggered, ContextObject, InputHeldFunc, Config.InputTag);
	}
}
