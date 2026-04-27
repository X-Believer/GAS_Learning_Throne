// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Widgets/ThroneWidgetBase.h"

#include "Components/UI/EnemyUIComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

void UThroneWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (const IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UThroneWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (const IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		
		checkf(EnemyUIComponent, TEXT("The Enemy Actor %s does not have an EnemyUIComponent!"), *OwningEnemyActor->GetActorNameOrLabel());
		BP_OwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
