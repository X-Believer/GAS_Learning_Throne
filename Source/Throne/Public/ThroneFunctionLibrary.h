// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThroneFunctionLibrary.generated.h"

struct FGameplayTag;
class UThroneAbilitySystemComponent;

UENUM()
enum class EThroneConfirmType : uint8
{
	Yes,
	No
};

/**
 * 
 */
UCLASS()
class THRONE_API UThroneFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UThroneAbilitySystemComponent* NativeGetThroneASCFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);
	
	static bool NativeDoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|FunctionLibrary", meta = (DisplayName="Does Actor Has Tag", ExpandEnumAsExecs="ConfirmType"))
	static void BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck, EThroneConfirmType& ConfirmType);
};
