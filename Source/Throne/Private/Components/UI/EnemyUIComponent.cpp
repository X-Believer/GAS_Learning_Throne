// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/ThroneWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UThroneWidgetBase* InWidget)
{
	EnemyDrawnWidgets.AddUnique(InWidget);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty()) return;
	
	for (UThroneWidgetBase* Widget : EnemyDrawnWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
	
	EnemyDrawnWidgets.Empty();
}
