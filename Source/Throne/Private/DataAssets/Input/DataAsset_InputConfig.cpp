// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FThroneInputActionConfig& Config : NativeInputActions)
	{
		if (Config.InputTag == InInputTag)
		{
			return Config.InputAction;
		}
	}
	
	return nullptr;
}
