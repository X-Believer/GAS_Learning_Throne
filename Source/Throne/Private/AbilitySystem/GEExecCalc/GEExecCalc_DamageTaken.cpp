// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAttributeSet.h"

struct FThroneDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);
	
	FThroneDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UThroneAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UThroneAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UThroneAttributeSet, DamageTaken, Target, false);
	}
};

static const FThroneDamageCapture& GetThroneDamageCapture()
{
	static FThroneDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetThroneDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetThroneDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetThroneDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();;
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetThroneDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	
	float BaseDamage = 0.f;
	int32 LightAttackComboCount = 0;
	int32 HeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(ThroneGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(ThroneGameplayTags::PlayerTag_SetByCaller_AttackType_Light))
		{
			LightAttackComboCount = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(ThroneGameplayTags::PlayerTag_SetByCaller_AttackType_Heavy))
		{
			HeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetThroneDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	
	if (LightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (LightAttackComboCount - 1) * 0.1f + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
	}
	if (HeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = HeavyAttackComboCount  * 0.8f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}
	const float FinalDamage = FMath::Max(BaseDamage * SourceAttackPower / TargetDefensePower, 0.f);
	
	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			GetThroneDamageCapture().DamageTakenProperty, 
			EGameplayModOp::Additive, 
			FinalDamage));
	}
}
