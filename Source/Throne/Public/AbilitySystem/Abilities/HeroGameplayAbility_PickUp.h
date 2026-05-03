// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"
#include "HeroGameplayAbility_PickUp.generated.h"

class AThroneStoneBase;
/**
 * 
 */
UCLASS()
class THRONE_API UHeroGameplayAbility_PickUp : public UThroneHeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UFUNCTION(BlueprintCallable)
	void CollectStones();
	
	UFUNCTION(BlueprintCallable)
	void ConsumeStones();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="PickUp")
	float BoxTraceDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="PickUp")
	FVector BoxTraceSize = FVector(100.f);
	
	UPROPERTY(EditDefaultsOnly, Category="PickUp")
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneRaceChannel;
	
	UPROPERTY(EditDefaultsOnly, Category="PickUp")
	bool bDrawDebugShape = false;
	
	UPROPERTY()
	TArray<AThroneStoneBase*> CollectedStones;
};
