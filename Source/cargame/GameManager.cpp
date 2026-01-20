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
	
	CarSpawnerOffset = -5000.0f;
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
	CarSpawnerActor->HandleTemplate(1);
	// FTimerDelegate TimerDelegate;
	// TimerDelegate.BindUFunction(this, "SpawnCar", CurrentRound);
	// GetWorldTimerManager().SetTimer(CarSpawnerTimer, TimerDelegate, FMath::FRandRange(1.0, 3.0), true);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
	UE_LOG(LogTemp,Warning, TEXT("New Spawner Loc %s"), *NewCarSpawnerLoc.ToString());
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
	APawn* Pawn= GetWorld()->GetFirstPlayerController()->GetPawn();
	if (Pawn) {
		PlayerActor = Cast<APlayerCharacter>(Pawn);
	}
	PlayerActor->SetPlayerMaxSpeed(CurrentGameDifficulty);
}

void AGameManager::SpawnCar(int Round)
{
	
}

//void AGameManager::PlayerSpawnInitialization()
//{
//	FActorSpawnParameters SpawnParameters;
//	SpawnParameters.Instigator = NULL;
//	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, PlayerLocation);
//	
//}

