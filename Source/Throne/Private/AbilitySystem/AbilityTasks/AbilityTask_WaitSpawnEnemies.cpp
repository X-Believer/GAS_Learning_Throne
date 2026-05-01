// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Characters/ThroneEnemyCharacter.h"
#include "Engine/AssetManager.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility,
                                                                               FGameplayTag EventTag, TSoftClassPtr<AThroneEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn,
                                                                               const FVector& SpawnLocation, float RandomSpawnRadius)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnLocation = SpawnLocation;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	
	return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
	Super::Activate();
	
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	DelegateHandle = Delegate.AddUObject(this, &UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived);
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool AbilityEnded)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);	
	Delegate.Remove(DelegateHandle);

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* Payload)
{
	if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CachedSoftEnemyClassToSpawn.ToSoftObjectPath(), 
		FStreamableDelegate::CreateUObject(this, &UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded));
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AThroneEnemyCharacter*>());
		}
		
		EndTask();
	}
}

void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();
	
	if (!World || !LoadedClass)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AThroneEnemyCharacter*>());
		}
		EndTask();
		return;
	}
	
	TArray<AThroneEnemyCharacter*> SpawnedEnemies;
	
	FActorSpawnParameters SpawnParas;
	SpawnParas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (int32 i = 0; i < CachedNumToSpawn; ++i)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnLocation, RandomLocation, CachedRandomSpawnRadius);
		
		RandomLocation += FVector(0.f, 0.f, 150.f);
		
		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();
		
		AThroneEnemyCharacter* SpawnedEnemy = World->SpawnActor<AThroneEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParas);
		
		if (SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (!SpawnedEnemies.IsEmpty())
		{
			OnSpawnFinished.Broadcast(SpawnedEnemies);
		}
		else
		{
			DidNotSpawn.Broadcast(TArray<AThroneEnemyCharacter*>());
		}
	}
	EndTask();
}
