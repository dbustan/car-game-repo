// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "Slate/SGameLayerManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	CarSpawnerInitialization();
	InitPlayer();
	CarSpawnerOffset = -7000.0f;
	/*PlayerSpawnInitialization();*/
	/*float CurrentGameDifficulty = 1;*/
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
	CarSpawnerActor->SpawnCar();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	UE_LOG(LogTemp,Warning, TEXT("New Spawner Loc %s"), *NewCarSpawnerLoc.ToString());
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
}

void AGameManager::CarSpawnerInitialization()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = NULL;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, CarSpawnerLocation);
	CarSpawnerActor = GetWorld()->SpawnActor<ACarSpawner>(CarSpawnerBP, SpawnTransform, SpawnParameters);
	
}

void AGameManager::InitPlayer()
{
	APawn* Pawn  = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (Pawn) {
		PlayerActor = Cast<APlayerCharacter>(Pawn);
	}
	PlayerActor->SetPlayerMaxSpeed(CurrentGameDifficulty);
}

//void AGameManager::PlayerSpawnInitialization()
//{
//	FActorSpawnParameters SpawnParameters;
//	SpawnParameters.Instigator = NULL;
//	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, PlayerLocation);
//	
//}

