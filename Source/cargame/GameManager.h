// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarSpawner.h"
#include "PlayerCharacter.h"
#include "GameManager.generated.h"

UCLASS()
class CARGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	TSubclassOf<ACarSpawner> CarSpawnerBP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	class ACarSpawner* CarSpawnerActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	FVector CarSpawnerLocation = FVector(-240.0, 130.0, 170.0);
	FTimerHandle CarSpawnerTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	float CurrentGameDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	float CarSpawnerOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int TotalRounds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int CurrentRound = 1;
	class APlayerCharacter* PlayerActor;
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void CarSpawnerInitialization();
	void InitPlayer();
	void SpawnCar(int Round);
	/*void PlayerSpawnInitialization();*/
};
