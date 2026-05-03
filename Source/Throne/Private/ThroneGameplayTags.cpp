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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Light, "InputTag.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Heavy, "InputTag.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp_Stones, "InputTag.PickUp.Stones");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Rage, "InputTag.Toggleable.Rage");
	
	/* Player Tags*/
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Weapon_Melee, "PlayerTag.Weapon.Melee");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Equip_Melee, "PlayerTag.Ability.Equip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Unequip_Melee, "PlayerTag.Ability.Unequip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Attack_Light_Melee, "PlayerTag.Ability.Attack.Light.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Attack_Heavy_Melee, "PlayerTag.Ability.Attack.Heavy.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_HitPause, "PlayerTag.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Roll, "PlayerTag.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Block, "PlayerTag.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_TargetLock, "PlayerTag.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_Rage, "PlayerTag.Ability.Rage");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_SpecialWeapon_Light, "PlayerTag.Ability.SpecialWeapon.Light");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_SpecialWeapon_Heavy, "PlayerTag.Ability.SpecialWeapon.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Ability_PickUp_Stones, "PlayerTag.Ability.PickUp.Stones");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Cooldown_SpecialWeapon_Light, "PlayerTag.Cooldown.SpecialWeapon.Light");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Cooldown_SpecialWeapon_Heavy, "PlayerTag.Cooldown.SpecialWeapon.Heavy");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Equip_Melee, "PlayerTag.Event.Equip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_Unequip_Melee, "PlayerTag.Event.Unequip.Melee");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_HitPause, "PlayerTag.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_SuccessfulBlock, "PlayerTag.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_SwitchTarget_Left, "PlayerTag.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_SwitchTarget_Right, "PlayerTag.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_ActivateRage, "PlayerTag.Event.ActivateRage");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_AOE, "PlayerTag.Event.AOE");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Event_ConsumeStone, "PlayerTag.Event.ConsumeStone");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_JumpToFinisher, "PlayerTag.Status.JumpToFinisher");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Rolling, "PlayerTag.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Blocking, "PlayerTag.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_TargetLock, "PlayerTag.Status.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Rage_Activating, "PlayerTag.Status.Rage.Activating");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Rage_Active, "PlayerTag.Status.Rage.Active");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Rage_Full, "PlayerTag.Status.Rage.Full");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_Status_Rage_None, "PlayerTag.Status.Rage.None");
	
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_SetByCaller_AttackType_Light, "PlayerTag.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(PlayerTag_SetByCaller_AttackType_Heavy, "PlayerTag.SetByCaller.AttackType.Heavy");
	
	/* Enemy Tags*/
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Ability_Melee, "EnemyTag.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Ability_Ranged, "EnemyTag.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Ability_SummonEnemy, "EnemyTag.Ability.SummonEnemy");
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Ability_SpawnStone, "EnemyTag.Ability.SpawnStone");
	
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Weapon, "EnemyTag.Weapon");
	
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Event_SummonEnemy, "EnemyTag.Event.SummonEnemy");
	
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Status_Strafing, "EnemyTag.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Status_UnderAttack, "EnemyTag.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(EnemyTag_Status_Unblockable, "EnemyTag.Status.Unblockable");
	
	/* Shared Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");
}