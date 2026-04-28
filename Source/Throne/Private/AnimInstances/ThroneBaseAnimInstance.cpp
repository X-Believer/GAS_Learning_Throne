// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AnimInstances/ThroneBaseAnimInstance.h"
#include "GameplayTagContainer.h"
#include "ThroneFunctionLibrary.h"

bool UThroneBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UThroneFunctionLibrary::NativeDoesActorHasTag(OwningPawn, TagToCheck);
	}
	
	return false;
}
