// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/ThronePickUpBase.h"
#include "ThroneStoneBase.generated.h"

class UGameplayEffect;
class UThroneAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class THRONE_API AThroneStoneBase : public AThronePickUpBase
{
	GENERATED_BODY()
	
public:
	void Consume(UThroneAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Stone Consumed"))
	void BP_OnStoneConsumed();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
