// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

class AThroneEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AThroneEnemyCharacter*>&, SpawnedEnemies);

/**
 * 
 */
UCLASS()
class THRONE_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Throne|AbilityTask", meta=(DisplayName="Wait Gameplay Event and Spawn Enemy",HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true",NumToSpawn="1",RandomSpawnRadius="200.0f"))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* OwningAbility, 
		FGameplayTag EventTag, 
		TSoftClassPtr<AThroneEnemyCharacter> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnLocation,
		float RandomSpawnRadius);	
	
	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;
	
	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;
	
protected:
	//~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
	//~ End UGameplayTask Interface
	
private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<AThroneEnemyCharacter> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	FVector CachedSpawnLocation;
	float CachedRandomSpawnRadius;
	
	FDelegateHandle DelegateHandle;
	
	void OnGameplayEventReceived(const FGameplayEventData* Payload);
	void OnEnemyClassLoaded();
};
