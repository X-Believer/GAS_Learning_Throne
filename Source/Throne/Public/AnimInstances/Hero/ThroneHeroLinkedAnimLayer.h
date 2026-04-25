// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ThroneBaseAnimInstance.h"
#include "ThroneHeroLinkedAnimLayer.generated.h"

class UThroneHeroAnimInstance;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneHeroLinkedAnimLayer : public UThroneBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe), Category = "Throne|Animation")
	UThroneHeroAnimInstance* GetHeroAnimInstance() const;
};
