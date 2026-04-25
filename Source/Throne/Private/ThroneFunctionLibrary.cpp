// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"

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
