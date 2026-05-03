#pragma once

UENUM()
enum class EThroneConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EThroneValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EThroneSuccessType : uint8
{
	Success,
	Failure
};

UENUM()
enum class EThroneCountdownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EThroneCountdownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EThroneGameDifficulty : uint8
{
	Easy,
	Medium,
	Hard,
	Brutal
};