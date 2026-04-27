// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ThroneWidgetBase.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningHeroUIComponentInitialized"))
	void BP_OwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningEnemyUIComponentInitialized"))
	void BP_OwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
