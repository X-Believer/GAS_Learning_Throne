// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Characters/ThroneBaseCharacter.h"

#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/ThroneAttributeSet.h"

// Sets default values
AThroneBaseCharacter::AThroneBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	GetMesh()->bReceivesDecals = false;

	ThroneAbilitySystemComponent = CreateDefaultSubobject<UThroneAbilitySystemComponent>(TEXT("ThroneAbilitySystemComponent"));
	ThroneAttributeSet = CreateDefaultSubobject<UThroneAttributeSet>(TEXT("ThroneAttributeSet"));
}

UAbilitySystemComponent* AThroneBaseCharacter::GetAbilitySystemComponent() const
{
	return GetThroneAbilitySystemComponent();
}

void AThroneBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (ThroneAbilitySystemComponent)
	{
		ThroneAbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("CharacterStartUpData is null! Please assign a StartUpData to %s"), *GetName());
	}
}
