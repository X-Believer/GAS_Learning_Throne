// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "ThroneBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UThroneAttributeSet;
class UThroneAbilitySystemComponent;

UCLASS()
class THRONE_API AThroneBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AThroneBaseCharacter();
	
	//~ Begin IAbilitySystemInterface 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface 
	
	//~ Begin PawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface 
	
	//~ Begin PawnUIInterface 
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End PawnUIInterface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UThroneAbilitySystemComponent> ThroneAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UThroneAttributeSet> ThroneAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	
public:
	FORCEINLINE UThroneAbilitySystemComponent* GetThroneAbilitySystemComponent() const { return ThroneAbilitySystemComponent; }
	FORCEINLINE UThroneAttributeSet* GetThroneAttributeSet() const { return ThroneAttributeSet; }
};
