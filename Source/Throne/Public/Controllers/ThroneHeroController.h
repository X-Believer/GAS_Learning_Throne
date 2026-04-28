// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "ThroneHeroController.generated.h"

/**
 * 
 */
UCLASS()
class THRONE_API AThroneHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AThroneHeroController();
	
	//~ Begin IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End	IGenericTeamAgentInterface
	
private:
	FGenericTeamId HeroTeamId;
};
