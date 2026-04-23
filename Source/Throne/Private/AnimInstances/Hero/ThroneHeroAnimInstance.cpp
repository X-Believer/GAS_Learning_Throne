// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AnimInstances/Hero/ThroneHeroAnimInstance.h"

#include "Characters/ThroneHeroCharacter.h"

void UThroneHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AThroneHeroCharacter>(OwningCharacter);
	}
}

void UThroneHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
	}
}
