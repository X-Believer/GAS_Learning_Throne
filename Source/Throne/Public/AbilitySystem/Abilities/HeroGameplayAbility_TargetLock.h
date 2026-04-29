// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ThroneHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UInputMappingContext;
class UThroneWidgetBase;
/**
 * 
 */
UCLASS()
class THRONE_API UHeroGameplayAbility_TargetLock : public UThroneHeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UFUNCTION(BlueprintCallable, Category = "Target Lock")
	void OnTargetLockTick(float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "Target Lock")
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);
	
private:
	bool TryLockOnTarget();
	void GetAvailableActorsToLock();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void ResetTargetLockMovement();
	void InitTargetLockMappingContext();
	void ResetTargetLockMappingContext();
	void CancelTargetLockAbility();
	void CleanUP();
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float BoxTraceDistance = 5000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector BoxTraceSize = FVector(5000.f, 5000.f, 300.f);
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<UThroneWidgetBase> TargetLockWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance = 20.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TObjectPtr<UInputMappingContext> TargetLockMappingContext;
	
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;
	
	UPROPERTY()
	AActor* CurrentLockedActor;
	
	UPROPERTY()
	TObjectPtr<UThroneWidgetBase> TargetLockWidget;
	
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
	
	UPROPERTY()
	float CacheDefaultMaxWalkSpeed = 0.f;
};
