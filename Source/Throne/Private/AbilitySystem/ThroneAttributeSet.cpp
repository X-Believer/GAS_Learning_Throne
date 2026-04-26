// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/ThroneAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "ThroneDebugHelper.h"

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
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewRage);
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float InDamageTaken = GetDamageTaken();
		
		const float NewHealth = FMath::Clamp(OldHealth - InDamageTaken, 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		
		Debug::Print("Damage Taken", InDamageTaken, FColor::Red);
		Debug::Print("New Health", NewHealth, FColor::Red);
		
		//TODO: Notify UI
		
		//TODO: Handle Death
	}
}
