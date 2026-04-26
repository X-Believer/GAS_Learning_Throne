// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AThroneWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class THRONE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	void RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister, AThroneWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	AThroneWeaponBase* GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	AThroneWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UPROPERTY(BlueprintReadWrite, Category = "Throne|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category = "Throne|Combat")
	void ToggleWeaponCollision(bool bShouldToggle, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);
	
	virtual void OnWeaponHitTargetActor(AActor* OtherActor);
	virtual void OnWeaponEndHitTargetActor(AActor* OtherActor);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Throne|Combat")
	TArray<AActor*> OverlappedActors;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AThroneWeaponBase*> CharacterCarriedWeaponMap;
};
