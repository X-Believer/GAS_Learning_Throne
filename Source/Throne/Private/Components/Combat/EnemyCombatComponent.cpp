// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ThroneGameplayTags.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* OtherActor)
{
	if (OverlappedActors.Contains(OtherActor)) return;
	
	OverlappedActors.AddUnique(OtherActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackBlockable = false;
	
	if (bIsPlayerBlocking && !bIsMyAttackBlockable)
	{
		
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = OtherActor;
	
	if (bIsValidBlock)
	{
		
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			ThroneGameplayTags::Shared_Event_MeleeHit,
			EventData);
	}
}
