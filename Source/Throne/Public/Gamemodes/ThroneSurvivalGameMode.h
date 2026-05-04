// Copyright (c) 2026 Shuyang Xing. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Gamemodes/ThroneBaseGameMode.h"
#include "ThroneSurvivalGameMode.generated.h"

class AThroneEnemyCharacter;

UENUM(BlueprintType)
enum class EThroneSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesCompleted,
	PlayerDeath
};

USTRUCT(BlueprintType)
struct FThroneEnemyWaveSpawnerInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AThroneEnemyCharacter> SoftEnemyClassToSpawn;
	
	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;
	
	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 1;
};

USTRUCT(BlueprintType)
struct FThroneEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FThroneEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedDelegate, EThroneSurvivalGameModeState, NewState);

/**
 * 
 */
UCLASS()
class THRONE_API AThroneSurvivalGameMode : public AThroneBaseGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AThroneEnemyCharacter*>& InEnemiesToRegister);
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	void SetCurrentSurvivalGameModeState(EThroneSurvivalGameModeState InState);
	bool HasFinishedAllWaves();
	void PreLoadNextWaveEnemies();
	FThroneEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemy() const;
	
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedEnemy);
	
	UPROPERTY()
	EThroneSurvivalGameModeState CurrentSurvivalGameModeState;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChanged;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDataTable> EnemyWaveSpawnerDataTable;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	int32 TotalWavesToSpawn;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	int32 CurrentWaveCount = 1;
	
	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;
	
	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;
	
	UPROPERTY()
	TArray<AActor*> TargetPoints;
	
	UPROPERTY()
	float TimePassedSinceStart = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	float SpawnNewWaveWaitTime = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	float SpawnEnemyDelayTime = 2.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave Definition", meta=(AllowPrivateAccess="true"))
	float WaveCompletedWaitTime = 5.f;
	
	UPROPERTY()
	TMap<TSoftClassPtr<AThroneEnemyCharacter>, UClass*> PreLoadedEnemyClassMap;
};
