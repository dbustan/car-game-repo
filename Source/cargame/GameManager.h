// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarSpawner.h"
#include "WindowsGameInstance.h"
#include  "Car.h"
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
	FTimerHandle CarMovementTimer;
	FTimerHandle PlayerMovementTimer;
	FTimerHandle RoundStartTimer;
	bool TimerStarted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* GameSong;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class UWindowsGameInstance* MyGameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	float CurrentGameDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	float CarSpawnerOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	int TotalRounds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	float RoundTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	float SetupTimer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int CurrentRound = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawner")
	ACar* LastPlacedCar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	class UBoxComponent* RoundEndCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
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
	void InitSound();
	UFUNCTION()
	void EndRound(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void StartRound();
	void StartRoundTimer();
	void StartMovement();
	UFUNCTION()
	void LostGame();
	/*void PlayerSpawnInitialization();*/
};
