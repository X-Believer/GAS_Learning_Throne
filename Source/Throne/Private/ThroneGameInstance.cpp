// Copyright (c) 2026 Shuyang Xing. All rights reserved.


#include "ThroneGameInstance.h"

#include "MoviePlayer.h"

void UThroneGameInstance::Init()
{
	Super::Init();
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UThroneGameInstance::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UThroneGameInstance::OnDestinationWorldLoaded);
}

void UThroneGameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
	
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UThroneGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

TSoftObjectPtr<UWorld> UThroneGameInstance::GetGameLevelByTag(FGameplayTag LevelTag) const
{
	for (const FThroneGameLevelSet& LevelSet : GameLevelSets)
	{
		if (!LevelSet.IsValid()) continue;
		
		if (LevelSet.LevelTag == LevelTag)
		{
			return LevelSet.Level;
		}
	}
	
	return TSoftObjectPtr<UWorld>();
}
