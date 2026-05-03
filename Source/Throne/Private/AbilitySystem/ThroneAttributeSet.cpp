// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/ThroneAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "ThroneFunctionLibrary.h"
#include "ThroneGameplayTags.h"
#include "Components/UI/HeroUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

UThroneAttributeSet::UThroneAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitDamageTaken(0.f);
}

void UThroneAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("CachedPawnUIInterface is not valid in UThroneAttributeSet::PostGameplayEffectExecute"));

	const UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("PawnUIComponent is not valid in UThroneAttributeSet::PostGameplayEffectExecute"));
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewRage);
		
		if (GetCurrentRage() == GetMaxRage())
		{
			UThroneFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), ThroneGameplayTags::PlayerTag_Status_Rage_Full);
		}
		else if (GetCurrentRage() == 0.f)
		{
			UThroneFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), ThroneGameplayTags::PlayerTag_Status_Rage_None);
		}
		else
		{
			UThroneFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), ThroneGameplayTags::PlayerTag_Status_Rage_Full);
			UThroneFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), ThroneGameplayTags::PlayerTag_Status_Rage_None);
		}
		
		if (const UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float InDamageTaken = GetDamageTaken();
		
		const float NewHealth = FMath::Clamp(OldHealth - InDamageTaken, 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		
		if (GetCurrentHealth() <= 0.f)
		{
			UThroneFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), ThroneGameplayTags::Shared_Status_Death);
		}
	}
}
