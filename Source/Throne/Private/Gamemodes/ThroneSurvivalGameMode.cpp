// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#include "Gamemodes/ThroneSurvivalGameMode.h"
#include "NavigationSystem.h"
#include "ThroneFunctionLibrary.h"
#include "Characters/ThroneEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void AThroneSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AThroneEnemyCharacter*>& InEnemiesToRegister)
{
	for (AThroneEnemyCharacter* Enemy : InEnemiesToRegister)
	{
		if (Enemy)
		{
			Enemy->OnDestroyed.AddUniqueDynamic(this, &AThroneSurvivalGameMode::OnEnemyDestroyed);
			CurrentSpawnedEnemiesCounter++;
		}
	}
}

void AThroneSurvivalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	EThroneGameDifficulty SavedDifficulty;
	
	if (UThroneFunctionLibrary::TryLoadSavedGameDifficulty(SavedDifficulty))
	{
		CurrentGameDifficulty = SavedDifficulty;
	}
}

void AThroneSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EnemyWaveSpawnerDataTable, TEXT("EnemyWaveSpawnerDataTable is not set in the editor! Please set it to a valid data table asset."));
	SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::WaitSpawnNewWave);
	
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
	
	PreLoadNextWaveEnemies();
}

void AThroneSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (CurrentSurvivalGameModeState == EThroneSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;
		
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			
			SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::SpawningNewWave);
		}
	}
	
	if (CurrentSurvivalGameModeState == EThroneSurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;
		
		if (TimePassedSinceStart >= SpawnEnemyDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
			TimePassedSinceStart = 0.f;
			
			SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::InProgress);
		}
	}
	
	if (CurrentSurvivalGameModeState == EThroneSurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaSeconds;
		
		if (TimePassedSinceStart >= WaveCompletedWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;
			
			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::AllWavesCompleted);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
		}
	}
}

void AThroneSurvivalGameMode::SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	
	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool AThroneSurvivalGameMode::HasFinishedAllWaves()
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AThroneSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves()) return;
	
	PreLoadedEnemyClassMap.Empty();
	
	for (FThroneEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(), 
			FStreamableDelegate::CreateLambda([SpawnerInfo, this]()
			{
				if (UClass* EnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
				{
					PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, EnemyClass);
				}
			})
		);
	}
}

FThroneEnemyWaveSpawnerTableRow* AThroneSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName CurrentWaveRowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));
	FThroneEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FThroneEnemyWaveSpawnerTableRow>(CurrentWaveRowName, FString());
	
	checkf(FoundRow, TEXT("Cannot find row with name %s in EnemyWaveSpawnerDataTable! Please make sure the data table has a row with this name."), *CurrentWaveRowName.ToString());
	
	return FoundRow;
}

int32 AThroneSurvivalGameMode::TrySpawnWaveEnemies()
{
	if (TargetPoints.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPoints);
	}
	
	checkf(!TargetPoints.IsEmpty(), TEXT("No TargetPoint actors found in the level! Please place at least one TargetPoint actor in the level for enemy spawning."));
	
	uint32 EnemiesSpawnedThisTime = 0;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (const FThroneEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		
		const int32 NumEnemiesToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);
		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);
		
		for (int32 i = 0; i < NumEnemiesToSpawn; i++)
		{
			const int32 TargetPointIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
			FVector SpawnLocation = TargetPoints[TargetPointIndex]->GetActorLocation();
			FRotator SpawnRotation = TargetPoints[TargetPointIndex]->GetActorForwardVector().ToOrientationRotator();
			
			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnLocation, RandomLocation, 500.f);
			
			RandomLocation.Z += 150.f;
			
			AThroneEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AThroneEnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParams);
			
			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &AThroneSurvivalGameMode::OnEnemyDestroyed);
				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}
			
			if (!ShouldKeepSpawnEnemy()) return EnemiesSpawnedThisTime;
		}
	}
	
	return EnemiesSpawnedThisTime;
}

bool AThroneSurvivalGameMode::ShouldKeepSpawnEnemy() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AThroneSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedEnemy)
{
	CurrentSpawnedEnemiesCounter--;
	
	if (ShouldKeepSpawnEnemy())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;
		
		SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState::WaveCompleted);
	}
}
