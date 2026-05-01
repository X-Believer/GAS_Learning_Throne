// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ThroneFunctionLibrary.h"
#include "ThroneGameplayTags.h"
#include "Characters/ThroneEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* OtherActor)
{
	if (OverlappedActors.Contains(OtherActor)) return;
	
	OverlappedActors.AddUnique(OtherActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = UThroneFunctionLibrary::NativeDoesActorHasTag(OtherActor, ThroneGameplayTags::PlayerTag_Status_Blocking);
	const bool bIsMyAttackBlockable = UThroneFunctionLibrary::NativeDoesActorHasTag(GetOwningPawn(), ThroneGameplayTags::EnemyTag_Status_Unblockable);
	
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

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldToggle, EToggleDamageType ToggleDamageType)
{
	Super::ToggleBodyCollisionBoxCollision(bShouldToggle, ToggleDamageType);
	
	AThroneEnemyCharacter* OwningEnemyCharacter = Cast<AThroneEnemyCharacter>(GetOwningPawn());
	check(OwningEnemyCharacter);
	
	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	
	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
		case EToggleDamageType::LeftHand:
			LeftHandCollisionBox->SetCollisionEnabled(bShouldToggle ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
			break;
		case EToggleDamageType::RightHand:
			RightHandCollisionBox->SetCollisionEnabled(bShouldToggle ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
			break;
		default:
			break;
	}
	
	if (!bShouldToggle)
	{
		OverlappedActors.Empty();
	}
}
