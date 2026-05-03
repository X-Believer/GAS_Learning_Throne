// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Items/PickUps/ThronePickUpBase.h"
#include "Components/SphereComponent.h"

AThronePickUpBase::AThronePickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AThronePickUpBase::OnPickUpCollisionSphereBeginOverlap);
}

void AThronePickUpBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


