// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Road = CreateDefaultSubobject<USceneComponent>(TEXT("Road"));
	PlayerCheckArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerArrow"));
	NextRoadArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RoadArrow"));
	PlayerDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerDetection"));
	RootComponent = Cube;
	PlayerDetection->SetupAttachment(Cube);
	PlayerDetection->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerDetection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	PlayerDetection->SetGenerateOverlapEvents(true);
	// Cube->SetupAttachment(RootComponent);
	Road->SetupAttachment(Cube);
	PlayerCheckArrow->SetupAttachment(Road);
	NextRoadArrow->SetupAttachment(Road);
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	//Remember to do this when using overlap techniques, links the call to the function
	PlayerDetection->OnComponentBeginOverlap.AddDynamic(this, &ARoad::OverlapBegin);
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (const APlayerController* PC =  GetWorld()->GetFirstPlayerController()) {
		if (APawn *Pawn = PC->GetPawn())
		{
			FVector PlayerLoc = Pawn->GetActorLocation();
			FVector PlayerArrowLoc = PlayerCheckArrow->GetComponentLocation();
			FVector Distance = PlayerArrowLoc - PlayerLoc;
			// UE_LOG(LogTemp, Display, TEXT("Distance : %f"), Distance.Size());
			if ((PlayerArrowLoc - PlayerLoc).Size() < 15000 && !RoadSpawned)
			{
				UE_LOG(LogTemp, Warning, TEXT("Threshold was passed"));
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FVector NextRoadLoc = NextRoadArrow->GetComponentLocation();
				FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, NextRoadLoc);
				GetWorld()->SpawnActor<AActor>(GetClass(), SpawnTransform, SpawnParameters);
				RoadSpawned = true;
			}
		}
	}
	if (SelfDestructTimer)
	{
		
		static float LogTimer = 0.0f;
		// UE_LOG(LogTemp, Warning, TEXT("LogTimer: %f"), LogTimer);
		LogTimer += DeltaTime;
		if (LogTimer >= 3.0f)
		{
			this->Destroy();
			LogTimer = 0.0f;
		}
	}
	
}

void ARoad::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SelfDestructTimer = true;
}


UArrowComponent* ARoad::GetArrowComponent()
{
	return PlayerCheckArrow;
}

