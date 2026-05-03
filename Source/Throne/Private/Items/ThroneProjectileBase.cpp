// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "Items/ThroneProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "ThroneDebugHelper.h"
#include "ThroneFunctionLibrary.h"
#include "ThroneGameplayTags.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AThroneProjectileBase::AThroneProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddDynamic(this, &AThroneProjectileBase::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AThroneProjectileBase::OnProjectileBeginOverlap);
	
	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 900.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
	InitialLifeSpan = 4.f;
}

void AThroneProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AThroneProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);
	
	if (!HitPawn || !UThroneFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}
	
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UThroneFunctionLibrary::NativeDoesActorHasTag(HitPawn, ThroneGameplayTags::PlayerTag_Status_Blocking);
	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UThroneFunctionLibrary::IsValidBlock(this, HitPawn);
	}
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn, 
			ThroneGameplayTags::PlayerTag_Event_SuccessfulBlock, 
			Data);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}
	Destroy();
}

void AThroneProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverLappedActors.Contains(OtherActor)) return;
	OverLappedActors.AddUnique(OtherActor);
	
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Target = HitPawn;
		Data.Instigator = GetInstigator();
		
		if (UThroneFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			HandleApplyProjectileDamage(HitPawn, Data);
		}
	}
}

void AThroneProjectileBase::HandleApplyProjectileDamage(APawn* HitPawn, const FGameplayEventData& InEventData)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("ProjectileDamageEffectSpecHandle is not valid! Please make sure to set it when spawn the projectile!"));
	const bool bSuccess = UThroneFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), HitPawn, ProjectileDamageEffectSpecHandle);
	
	if (bSuccess)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn, 
			ThroneGameplayTags::Shared_Event_HitReact, 
			InEventData);
	}
}

