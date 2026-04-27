// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#include "Characters/ThroneHeroCharacter.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "ThroneGameplayTags.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Input/ThroneInputComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AThroneHeroCharacter::AThroneHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

void AThroneHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ThroneAbilitySystemComponent);
		}
	}
}

UPawnCombatComponent* AThroneHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AThroneHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AThroneHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AThroneHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is null!"));
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	
	UThroneInputComponent* ThroneInputComponent = CastChecked<UThroneInputComponent>(PlayerInputComponent);
	ThroneInputComponent->BindNativeAction(InputConfigDataAsset, ThroneGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AThroneHeroCharacter::Input_Move);
	ThroneInputComponent->BindNativeAction(InputConfigDataAsset, ThroneGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AThroneHeroCharacter::Input_Look);
	
	ThroneInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AThroneHeroCharacter::Input_AbilityInputPressed, &AThroneHeroCharacter::Input_AbilityInputReleased, &AThroneHeroCharacter::Input_AbilityInputHeld);
}

void AThroneHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AThroneHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation (0.f, GetControlRotation().Yaw, 0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AThroneHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.IsNearlyZero())
	{
		return;
	}
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AThroneHeroCharacter::Input_AbilityInputPressed(const FGameplayTag InInputTag)
{
	ThroneAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AThroneHeroCharacter::Input_AbilityInputReleased(const FGameplayTag InInputTag)
{
	ThroneAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

void AThroneHeroCharacter::Input_AbilityInputHeld(const FGameplayTag InInputTag)
{
	ThroneAbilitySystemComponent->OnAbilityInputHeld(InInputTag);
}
