// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	virtual void OnWeaponHitTargetActor(AActor* OtherActor) override;
	
protected:
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldToggle, EToggleDamageType ToggleDamageType) override;
};
