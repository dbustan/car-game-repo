// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

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
	/*PlayerSpawnInitialization();*/
	/*float CurrentGameDifficulty = 1;*/
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

