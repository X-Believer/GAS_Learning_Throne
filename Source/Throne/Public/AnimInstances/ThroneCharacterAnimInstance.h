// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ThroneBaseAnimInstance.h"
#include "ThroneCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AThroneBaseCharacter;
/**
 * 
 */
UCLASS()
class THRONE_API UThroneCharacterAnimInstance : public UThroneBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	TObjectPtr<AThroneBaseCharacter> OwningCharacter;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};
