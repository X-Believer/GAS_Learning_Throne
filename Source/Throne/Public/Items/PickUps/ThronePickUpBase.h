// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThronePickUpBase.generated.h"

class USphereComponent;

UCLASS()
class THRONE_API AThronePickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AThronePickUpBase();
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "PickUpInteraction")
	TObjectPtr<USphereComponent> PickUpCollisionSphere;
	
	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
