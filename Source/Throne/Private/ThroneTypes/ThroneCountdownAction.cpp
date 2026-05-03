// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneTypes/ThroneCountdownAction.h"

void FThroneCountdownAction::UpdateOperation(FLatentResponse& Response)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateOperation Tick"));
	
	if (bNeedToCancel)
	{
		CountdownOutput = EThroneCountdownActionOutput::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputPinLink, CallbackTarget);
		return;
	}
	
	if (ElapsedTimeSinceStarted >= TotalCountdownTime)
	{
		CountdownOutput = EThroneCountdownActionOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputPinLink, CallbackTarget);
		return;
	}
	
	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStarted += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		OutRemainingTime = TotalCountdownTime - ElapsedTimeSinceStarted;
		CountdownOutput = EThroneCountdownActionOutput::Updated;
		Response.TriggerLink(ExecutionFunction, OutputPinLink, CallbackTarget);
		ElapsedInterval = 0.f;
	}

}

void FThroneCountdownAction::CancelAction()
{
	bNeedToCancel = true;
}
