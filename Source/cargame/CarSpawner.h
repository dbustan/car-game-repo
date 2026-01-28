// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "WhiteCar.h"
#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Math/UnrealMathUtility.h"
#include "CarSpawner.generated.h"

USTRUCT(BlueprintType)
struct FLevelConfigRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<ACar>, int32> CarWeights;
};
UCLASS()
class CARGAME_API ACarSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
	UDataTable* LevelConfigTable;
	
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	FHitResult Hit;
	FTimerHandle DestroyTemplateTimer;
	UPROPERTY(EditDefaultsOnly)
	FVector StartPos;
	
	UPROPERTY(EditDefaultsOnly)
	FVector EndPos;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> AllRoundTemplates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	TArray<USceneComponent*> SpawnPoints;
	UPROPERTY(EditDefaultsOnly, Category = "CarSpawning")
	TMap<FName, TSubclassOf<ACar>> AllCarsMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	AActor* RoundTemplateActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Round")
	ACar* LastCar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Round")
	TArray<ACar*> CurrentlySpawnedCars;
public:	
	ACarSpawner();
	virtual void Tick(float DeltaTime) override;
	void SetGameSpeed(float NewSpeed);
	void HandleTemplate(int Round);
	ACar* GetLastCar();
	void DestroyAllInfo();
	void StartCarMovement();
	TArray<ACar*> GetAllCarsSpawned();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void HandleCarSpawning(USceneComponent* SpawnPoint, int Round);
	void DestroyTemplate();
	TSubclassOf<ACar> ChooseCar(FLevelConfigRow* LevelData);
	// Called every frame
	
};
