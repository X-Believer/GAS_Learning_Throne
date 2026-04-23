// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AnimInstances/ThroneCharacterAnimInstance.h"

#include "Characters/ThroneBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UThroneCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwningCharacter = Cast<AThroneBaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UThroneCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = !OwningMovementComponent->GetCurrentAcceleration().IsNearlyZero();
}
