// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Controllers/ThroneHeroController.h"

AThroneHeroController::AThroneHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AThroneHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
