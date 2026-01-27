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
	RoundEndCollider->SetupAttachment(RootComponent);
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
	InitSound();
	
	CurrentRound = 1;
	SetupTimer = 3.0f;
	RoundTimer = 10.0f;
	
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
	
	if (RoundTimer > 0 && TimerStarted)
	{
		RoundTimer -= DeltaTime;
		int32 JustSeconds = FMath::FloorToInt(RoundTimer);
		int32 Milliseconds = FMath::FloorToInt((RoundTimer - JustSeconds) * 100);
		FNumberFormattingOptions Options;
		Options.MinimumIntegralDigits = 2;
		FText SecText = FText::AsNumber(JustSeconds, &Options);
		FText MsText = FText::AsNumber(Milliseconds, &Options);
		PlayerActor->UpdateTimerUI(FText::Format(INVTEXT("{0}:{1}"), SecText, MsText));
	} else if (RoundTimer <= 0 && TimerStarted)
	{
		TimerStarted = false;
		LostGame();
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

void AGameManager::InitSound()
{
	UGameInstance * GeneralGameInstance = GetWorld()->GetGameInstance();
	MyGameInstance = Cast<UWindowsGameInstance>(GeneralGameInstance);
	if (MyGameInstance)
	{
		MyGameInstance->PlayMusic(0.0f, 0.0f, GameSong);
	}
}

void AGameManager::EndRound(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Error, TEXT("Player End"));
	CarSpawnerActor->DestroyAllInfo();
	CurrentRound++;
	StartRound();
	RoundTimer = 10.0f;
	int32 JustSeconds = FMath::FloorToInt(RoundTimer);
	int32 Milliseconds = FMath::FloorToInt((RoundTimer - JustSeconds) * 100);
	FNumberFormattingOptions Options;
	Options.MinimumIntegralDigits = 2;
	FText SecText = FText::AsNumber(JustSeconds, &Options);
	FText MsText = FText::AsNumber(Milliseconds, &Options);
	PlayerActor->UpdateTimerUI(FText::Format(INVTEXT("{0}:{1}"), SecText, MsText));
	TimerStarted = false;
	
}

void AGameManager::StartRound()
{
	if (!PlayerDead)
	{
		CarSpawnerActor->HandleTemplate(CurrentRound);
		LastPlacedCar = CarSpawnerActor->GetLastCar();
		PlayerActor->SetCanMove(false);
		if (CurrentRound != 1)
		{
			PlayerActor->ChangeRoundIcon(CurrentRound);
			PlayerActor->UpdateRoundStartTimerUI(SetupTimer);
			PlayerActor->StartRoundUITween();
		
		}
		TArray<ACar*> AllCars = CarSpawnerActor->GetAllCarsSpawned();
		for (ACar* Car : AllCars)
		{
			Car->OnTargetHit.AddDynamic(this, &AGameManager::LostGame);
		}
		StartMovement();
	}
}

void AGameManager::StartRoundTimer()
{
	TimerStarted = true;
}

void AGameManager::StartMovement()
{
	GetWorldTimerManager().SetTimer(CarMovementTimer, CarSpawnerActor, &ACarSpawner::StartCarMovement, SetupTimer, false);
	GetWorldTimerManager().SetTimer(PlayerMovementTimer, PlayerActor, &APlayerCharacter::EnablePlayerMovement, SetupTimer, false);
	GetWorldTimerManager().SetTimer(RoundStartTimer, this, &AGameManager::StartRoundTimer, SetupTimer, false);
}

void AGameManager::LostGame()
{
	if (!PlayerDead)
	{
		PlayerActor->SetCanMove(false);
		TimerStarted = false;
		PlayerDead = true;
		PlayerActor->UpdateTimerUI(FText::FromString("Game Over"));
		PlayerActor->SetupGameOver();
		MyGameInstance->PlaySound(DeathSound, 1.0f);
	}
}




