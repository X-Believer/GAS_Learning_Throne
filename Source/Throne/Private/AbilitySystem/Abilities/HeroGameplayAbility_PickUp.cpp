// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUp.h"

#include "Characters/ThroneHeroCharacter.h"
#include "Components/UI/HeroUIComponent.h"
#include "Items/PickUps/ThroneStoneBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UHeroGameplayAbility_PickUp::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_PickUp::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(false);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_PickUp::CollectStones()
{
	CollectedStones.Empty();
	
	TArray<FHitResult> TraceHit;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		BoxTraceSize / 2.f,
		(- GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneRaceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHit,
		true);
	
	for (const FHitResult& HitResult : TraceHit)
	{
		if (AThroneStoneBase* Stone = Cast<AThroneStoneBase>(HitResult.GetActor()))
		{
			CollectedStones.AddUnique(Stone);
		}
	}
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UHeroGameplayAbility_PickUp::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	
	for (AThroneStoneBase* Stone : CollectedStones)
	{
		Stone->Consume(GetThroneAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
	}
}
