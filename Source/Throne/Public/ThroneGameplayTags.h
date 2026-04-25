// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace ThroneGameplayTags
{
	/* Input Tags*/
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Light_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Heavy_Melee);
	
	/* Player Tags*/
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Weapon_Melee);
	
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Equip_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Unequip_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Attack_Light_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Ability_Attack_Heavy_Melee);
	
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Event_Equip_Melee);
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Event_Unequip_Melee);
	
	THRONE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerTag_Status_JumpToFinisher);
}
