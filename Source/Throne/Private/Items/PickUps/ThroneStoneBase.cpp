// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Items/PickUps/ThroneStoneBase.h"
#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Characters/ThroneHeroCharacter.h"

void AThroneStoneBase::Consume(UThroneAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	const UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext());
	
	BP_OnStoneConsumed();
}

void AThroneStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickUpCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (const AThroneHeroCharacter* OverlappedHeroCharacter = Cast<AThroneHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetThroneAbilitySystemComponent()->TryActivateAbilityByTag(ThroneGameplayTags::PlayerTag_Ability_PickUp_Stones);
	}
}
