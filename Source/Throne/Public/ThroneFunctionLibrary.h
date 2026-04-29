// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThroneTypes/ThroneEnumTypes.h"
#include "ThroneFunctionLibrary.generated.h"

struct FScalableFloat;
class UPawnCombatComponent;
struct FGameplayTag;
class UThroneAbilitySystemComponent;

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
	
	UFUNCTION(BlueprintCallable, Category = "Throne|FunctionLibrary", meta = (DisplayName="DoesActorHasTag", ExpandEnumAsExecs="ConfirmType"))
	static void BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck, EThroneConfirmType& ConfirmType);
	
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|FunctionLibrary", meta = (DisplayName = "GetPawnCombatComponentFromActor", ExpandEnumAsExecs="ValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EThroneValidType& ValidType);
	
	UFUNCTION(BlueprintPure, Category = "Throne|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* SourcePawn, APawn* TargetPawn);
	
	UFUNCTION(BlueprintPure, Category = "Throne|FunctionLibrary",meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& ScalableFloat, int32 InLevel);
	
	UFUNCTION(BlueprintPure, Category = "Throne|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(const AActor* SourceActor, const AActor* TargetActor, float& OutAngleDiff);
	
	UFUNCTION(BlueprintPure, Category = "Throne|FunctionLibrary")
	static bool IsValidBlock(const AActor* InAttackingActor, const AActor* InDefendingActor);
};
