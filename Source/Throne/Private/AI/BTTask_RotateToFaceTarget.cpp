// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "AI/BTTask_RotateToFaceTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
	NodeName = TEXT("Native Rotate To Face Target Actor");
	AnglePrecision = 10.f;
	RotationInterpSpeed = 5.f;
	
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	
	INIT_TASK_NODE_NOTIFY_FLAGS();
	
	InTargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RotateToFaceTarget, InTargetToFaceKey), AActor::StaticClass());
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	
	if (const UBlackboardData* BlackboardData = GetBlackboardAsset())
	{
		InTargetToFaceKey.ResolveSelectedKey(*BlackboardData);
	}
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
	return sizeof(FRotateToFaceTargetTaskMemory);
	
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
	const FString TargetDesc = InTargetToFaceKey.IsSet() ? InTargetToFaceKey.SelectedKeyName.ToString() : TEXT("Invalid");
	return FString::Printf(TEXT("Rotate to face %s until angle precision %s"), *TargetDesc, *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);
	
	APawn* OwningPawn =  OwnerComp.GetAIOwner()->GetPawn();
	
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	check(Memory);
	
	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;
	
	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}
	if (HasReachedAnglePrecision(OwningPawn, TargetActor))
	{
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	
	if (!Memory->IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator NewRot = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		Memory->OwningPawn->SetActorRotation(NewRot);
	}
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(const APawn* QueryPawn, const AActor* TargetActor) const
{
	const FVector OwnerForwardVector = QueryPawn->GetActorForwardVector();
	const FVector DirectionToTarget = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).GetSafeNormal();
	
	const float DotResult = FVector::DotProduct(OwnerForwardVector, DirectionToTarget);
	const float Angle = UKismetMathLibrary::DegAcos(DotResult);
	
	return Angle <= AnglePrecision;
}
