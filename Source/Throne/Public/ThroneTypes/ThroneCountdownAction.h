// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThroneEnumTypes.h"

class FThroneCountdownAction : public FPendingLatentAction
{
public:
	FThroneCountdownAction(float InTotalCountdownTime, float InUpdateInterval, float& InOutRemainingTime, EThroneCountdownActionOutput& InCountdownOutput, const FLatentActionInfo& LatentInfo)
		:bNeedToCancel(false)
		, TotalCountdownTime(InTotalCountdownTime)
		, UpdateInterval(InUpdateInterval)
		, OutRemainingTime(InOutRemainingTime)
		, CountdownOutput(InCountdownOutput)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputPinLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, ElapsedInterval(0.f)
		, ElapsedTimeSinceStarted(0.f){}
	
	virtual void UpdateOperation(FLatentResponse& Response) override;
	
	void CancelAction();
	
private:
	bool bNeedToCancel;
	float TotalCountdownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EThroneCountdownActionOutput& CountdownOutput;
	FName ExecutionFunction;
	int32 OutputPinLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStarted;
};
