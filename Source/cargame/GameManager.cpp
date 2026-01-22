// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "Materials/MaterialExpressionOperator.h"
#include "Slate/SGameLayerManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoundEndCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RoundEnd"));
	RoundEndCollider->SetupAttachment(RoundEndCollider);
	RoundEndCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	RoundEndCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RoundEndCollider->OnComponentBeginOverlap.AddDynamic(this, &AGameManager::EndRound);
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	CarSpawnerInitialization();
	InitPlayer();
	CurrentRound = 1;
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
	StartRound();
	

}


void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CurrentCarSpawnerLoc = CarSpawnerActor->GetActorLocation();
	FVector NewCarSpawnerLoc = FVector(CurrentCarSpawnerLoc.X, PlayerLocation.Y + CarSpawnerOffset, CurrentCarSpawnerLoc.Z);
	CarSpawnerActor->SetActorLocation(NewCarSpawnerLoc);
	if (LastPlacedCar)
	{
		
		FVector LastPlacedCarLocation = LastPlacedCar->GetActorLocation();
		FVector RoundEndLocation = FVector(NewCarSpawnerLoc.X, LastPlacedCarLocation.Y - 150, LastPlacedCarLocation.Z);
		RoundEndCollider->SetWorldLocation(RoundEndLocation);
	}
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

void AGameManager::EndRound(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Error, TEXT("Player End"));
	CarSpawnerActor->DestroyAllInfo();
	CurrentRound++;
	StartRound();
	// UE_LOG(LogTemp, Warning, TEXT("Last Placed Car Name: %s"), *LastPlacedCar->GetName());
}

void AGameManager::StartRound()
{
	CarSpawnerActor->HandleTemplate(CurrentRound);
	LastPlacedCar = CarSpawnerActor->GetLastCar();
	PlayerActor->SetCanMove(false);
	StartMovement();
}

void AGameManager::StartMovement()
{
	GetWorldTimerManager().SetTimer(CarMovementTimer, CarSpawnerActor, &ACarSpawner::StartCarMovement, TimeBetweenRounds, false);
	GetWorldTimerManager().SetTimer(PlayerMovementTimer, PlayerActor, &APlayerCharacter::EnablePlayerMovement, TimeBetweenRounds, false);
}




