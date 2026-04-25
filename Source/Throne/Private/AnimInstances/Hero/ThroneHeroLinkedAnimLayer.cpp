// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AnimInstances/Hero/ThroneHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/ThroneHeroAnimInstance.h"

UThroneHeroAnimInstance* UThroneHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UThroneHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
