// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Characters/ThroneBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "ThroneTypes/ThroneCountdownAction.h"

UThroneAbilitySystemComponent* UThroneFunctionLibrary::NativeGetThroneASCFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UThroneAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UThroneFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UThroneAbilitySystemComponent* ASC = NativeGetThroneASCFromActor(InActor);
	
	if (ASC && !ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UThroneFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UThroneAbilitySystemComponent* ASC = NativeGetThroneASCFromActor(InActor);

	if (ASC && ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UThroneFunctionLibrary::NativeDoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UThroneAbilitySystemComponent* ASC = NativeGetThroneASCFromActor(InActor);

	return ASC && ASC->HasMatchingGameplayTag(TagToCheck);
}

void UThroneFunctionLibrary::BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck,
	EThroneConfirmType& ConfirmType)
{
	NativeDoesActorHasTag(InActor, TagToCheck) ? ConfirmType = EThroneConfirmType::Yes : ConfirmType = EThroneConfirmType::No;
}

UPawnCombatComponent* UThroneFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	
	if (const IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UThroneFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EThroneValidType& ValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	ValidType = PawnCombatComponent ? EThroneValidType::Valid : EThroneValidType::Invalid;
	return PawnCombatComponent;
}

bool UThroneFunctionLibrary::IsTargetPawnHostile(APawn* SourcePawn, APawn* TargetPawn)
{
	check(SourcePawn && TargetPawn);

	const IGenericTeamAgentInterface* SourceTeamAgent = Cast<IGenericTeamAgentInterface>(SourcePawn->GetController());
	const IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	
	if (SourceTeamAgent && TargetTeamAgent)
	{
		return SourceTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	
	return false;
}

float UThroneFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& ScalableFloat, const int32 InLevel)
{
	return ScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UThroneFunctionLibrary::ComputeHitReactDirectionTag(const AActor* SourceActor, const AActor* TargetActor, float& OutAngleDiff)
{
	check(SourceActor && TargetActor);
	
	const FVector TargetToSource = (SourceActor->GetActorLocation() - TargetActor->GetActorLocation()).GetSafeNormal();
	const FVector TargetForward = TargetActor->GetActorForwardVector();
	
	const float DotResult = FVector::DotProduct(TargetToSource, TargetForward);
	OutAngleDiff = UKismetMathLibrary::DegAcos(DotResult);
	
	const FVector CrossProduct = FVector::CrossProduct(TargetForward, TargetToSource);
	OutAngleDiff *= CrossProduct.Z < 0 ? -1.f : 1.f;
	
	if (OutAngleDiff >= -45.f && OutAngleDiff <= 45.f)
	{
		return ThroneGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDiff > 45.f && OutAngleDiff <= 135.f)
	{
		return ThroneGameplayTags::Shared_Status_HitReact_Right;
	}
	else if (OutAngleDiff < -45.f && OutAngleDiff >= -135.f)
	{
		return ThroneGameplayTags::Shared_Status_HitReact_Left;
	}
	else
	{
		return ThroneGameplayTags::Shared_Status_HitReact_Back;
	}
}

bool UThroneFunctionLibrary::IsValidBlock(const AActor* InAttackingActor, const AActor* InDefendingActor)
{
	check(InAttackingActor && InDefendingActor);
	
	const float DotProduct = FVector::DotProduct(InAttackingActor->GetActorForwardVector(), InDefendingActor->GetActorForwardVector());
	return DotProduct < -0.1f;
}

bool UThroneFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UThroneAbilitySystemComponent* SourceASC = NativeGetThroneASCFromActor(InInstigator);
	UThroneAbilitySystemComponent* TargetASC = NativeGetThroneASCFromActor(InTargetActor);
	
	FActiveGameplayEffectHandle ActiveEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data.Get(), TargetASC);
	return ActiveEffectHandle.WasSuccessfullyApplied();
}

void UThroneFunctionLibrary::Countdown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EThroneCountdownActionInput CountdownInput, UPARAM(DisplayName="Output") EThroneCountdownActionOutput& CountdownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;
	
	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}
	if (!World) return;
	
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FThroneCountdownAction* FoundAction = LatentActionManager.FindExistingAction<FThroneCountdownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	
	if (CountdownInput == EThroneCountdownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget, 
				LatentInfo.UUID, 
				new FThroneCountdownAction(TotalTime, UpdateInterval, OutRemainingTime, CountdownOutput, LatentInfo));
		}
	}
	
	if (CountdownInput == EThroneCountdownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}
