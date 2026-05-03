// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ThroneBaseCharacter.h"
#include "ThroneHeroCharacter.generated.h"

class UHeroUIComponent;
struct FGameplayTag;
class UHeroCombatComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class THRONE_API AThroneHeroCharacter : public AThroneBaseCharacter
{
	GENERATED_BODY()
	
public:
	AThroneHeroCharacter();
	
	//~ Begin PawnUIInterface 
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End PawnUIInterface 
	
protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	//~ Begin PawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface 
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHeroCombatComponent> HeroCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHeroUIComponent> HeroUIComponent;
	
#pragma endregion
	
#pragma region Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;
	
	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);
	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputPressed(const FGameplayTag InInputTag);
	void Input_AbilityInputReleased(const FGameplayTag InInputTag);
	void Input_AbilityInputHeld(const FGameplayTag InInputTag);
	
#pragma endregion
	
public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
