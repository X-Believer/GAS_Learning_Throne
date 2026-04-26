#pragma once

namespace Debug
{
	static void Print(const FString& Message, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, Color, Message);
			
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
	
	static void Print(const FString& Title, float Value, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString Message = Title + ": " + FString::SanitizeFloat(Value);
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, Color, Message);
			
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}
