// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "EnhancedInputSubsystems.h"
#include "ThroneFunctionLibrary.h"
#include "ThroneGameplayTags.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/ThroneHeroCharacter.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Controllers/ThroneHeroController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/ThroneWidgetBase.h"

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!TryLockOnTarget())
	{
		CleanUP();
		return;
	}
	InitTargetLockMovement();
	InitTargetLockMappingContext();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUP();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor || 
		UThroneFunctionLibrary::NativeDoesActorHasTag(CurrentLockedActor, ThroneGameplayTags::Shared_Status_Death) ||
		UThroneFunctionLibrary::NativeDoesActorHasTag(GetHeroCharacterFromActorInfo(), ThroneGameplayTags::Shared_Status_Death))
	{
		CancelTargetLockAbility();
		return;
	}
	
	SetTargetLockWidgetPosition();
	
	const bool bShouldOverrideRotation = !UThroneFunctionLibrary::NativeDoesActorHasTag(GetHeroCharacterFromActorInfo(), ThroneGameplayTags::PlayerTag_Status_Rolling)
	&& !UThroneFunctionLibrary::NativeDoesActorHasTag(GetHeroCharacterFromActorInfo(), ThroneGameplayTags::PlayerTag_Status_Blocking);
	
	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetHeroCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
		
		LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.0f, 0.0f);
		const FRotator CurrentControlRot = GetHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);
		
		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, CurrentControlRot.Roll));
		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UHeroGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();
	
	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewActorToLock;
	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);
	
	if (InSwitchDirectionTag == ThroneGameplayTags::PlayerTag_Event_SwitchTarget_Left && !ActorsOnLeft.IsEmpty())
	{
		NewActorToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else if (InSwitchDirectionTag == ThroneGameplayTags::PlayerTag_Event_SwitchTarget_Right && !ActorsOnRight.IsEmpty())
	{
		NewActorToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}
	else
	{
		return;
	}
	if (NewActorToLock)
	{
		CurrentLockedActor = NewActorToLock;
	}
}

bool UHeroGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
	
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return false;
	}
	
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
	
	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
		return true;
	}

	CancelTargetLockAbility();
	return false;
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	TArray<FHitResult> BoxTraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + BoxTraceSize / 4 ,
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		BoxTraceSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true);
	
	for (const FHitResult& Hit : BoxTraceHits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UHeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = FLT_MAX;
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	
	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	
	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;
		
		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		const FVector CrossProduct = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);
		
		if (CrossProduct.Z < 0.f)
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
		else if (CrossProduct.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
	}
}

void UHeroGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (TargetLockWidget) return;
	
	checkf(TargetLockWidgetClass, TEXT("TargetLockWidgetClass is null!"));
	
	TargetLockWidget = CreateWidget<UThroneWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);
	
	check(TargetLockWidget);
	
	TargetLockWidget->AddToViewport();
}

void UHeroGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}
	FVector2D ScreenPosition;
	
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetHeroControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
		);
	
	if (TargetLockWidgetSize.IsZero())
	{
		TargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* Widget)
		{
			if (const USizeBox* FoundSizeBox = Cast<USizeBox>(Widget))
			{
				TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
				TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
			}
		});
	}
	
	ScreenPosition -= TargetLockWidgetSize / 2.f;
	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMovement()
{
	CacheDefaultMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CacheDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CacheDefaultMaxWalkSpeed;
	}
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);
	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo()) return;
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);
	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

void UHeroGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UHeroGameplayAbility_TargetLock::CleanUP()
{
	AvailableActorsToLock.Empty();
	
	CurrentLockedActor = nullptr;
	
	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
	}
	
	TargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
	CacheDefaultMaxWalkSpeed = 0.f;
}
