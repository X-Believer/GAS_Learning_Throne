// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ThroneFunctionLibrary.h"
#include "ThroneGameplayTags.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* OtherActor)
{
	if (OverlappedActors.Contains(OtherActor)) return;
	
	OverlappedActors.AddUnique(OtherActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = UThroneFunctionLibrary::NativeDoesActorHasTag(OtherActor, ThroneGameplayTags::PlayerTag_Status_Blocking);
	const bool bIsMyAttackBlockable = false;
	
	if (bIsPlayerBlocking && !bIsMyAttackBlockable)
	{
		bIsValidBlock = UThroneFunctionLibrary::IsValidBlock(GetOwningPawn(), OtherActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = OtherActor;
	
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			OtherActor,
			ThroneGameplayTags::PlayerTag_Event_SuccessfulBlock,
			EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			ThroneGameplayTags::Shared_Event_MeleeHit,
			EventData);
	}
}
