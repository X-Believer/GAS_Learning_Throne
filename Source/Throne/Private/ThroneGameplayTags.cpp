// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneGameplayTags.h"

namespace ThroneGameplayTags
{
	/* Input Tags*/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Melee, "InputTag.Equip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Melee, "InputTag.Unequip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light_Melee, "InputTag.Attack.Light.Melee");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy_Melee, "InputTag.Attack.Heavy.Melee");
	
	/* Player Tags*/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Weapon_Melee, "PlayerTag.Weapon.Melee");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Equip_Melee, "PlayerTag.Ability.Equip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Unequip_Melee, "PlayerTag.Ability.Unequip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Attack_Light_Melee, "PlayerTag.Ability.Attack.Light.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Attack_Heavy_Melee, "PlayerTag.Ability.Attack.Heavy.Melee");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Equip_Melee, "PlayerTag.Event.Equip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Unequip_Melee, "PlayerTag.Event.Unequip.Melee");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_JumpToFinisher, "PlayerTag.Status.JumpToFinisher");
}