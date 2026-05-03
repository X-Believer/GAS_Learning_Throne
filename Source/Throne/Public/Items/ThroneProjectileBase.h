// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "ThroneProjectileBase.generated.h"

struct FGameplayEventData;
class UNiagaraComponent;
class UProjectileMovementComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EProjectileDamagePolicy : uint8
{
	OnHit,
	OnBeginOverlap
};

UCLASS()
class THRONE_API AThroneProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AThroneProjectileBase();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<UBoxComponent> ProjectileCollisionBox;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<UNiagaraComponent> ProjectileNiagaraComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileDamagePolicy ProjectileDamagePolicy = EProjectileDamagePolicy::OnHit;
	
	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle ProjectileDamageEffectSpecHandle;
	
	
	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);
	
private:
	void HandleApplyProjectileDamage(APawn* HitPawn, const FGameplayEventData& InEventData);
	
	UPROPERTY()
	TArray<AActor*> OverLappedActors;
};
