// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

#include "PlayerCharacter.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CarScene = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));
	CarScene->SetupAttachment(RootComponent);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CarScene);
	CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CarCollider"));
	CarCollision->SetupAttachment(SkeletalMesh);
	CarCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	CarCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	CarCollision->OnComponentBeginOverlap.AddDynamic(this, &ACar::KillPlayer);
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	CanMove = true;
}

void ACar::KillPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnTargetHit.Broadcast();
}


// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(DeltaTime);
}

void ACar::InitSpawnProperties(float ActionSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("WHAT"));
}



void ACar::MoveForward(float DeltaTime)
{
	if (CanMove)
	{
		// UE_LOG(LogTemp, Error, TEXT("%d"), CanMove);
		Location = GetActorLocation();
		Location += GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(Location);
	}
}

void ACar::SetMoving(bool NewMovement)
{
	CanMove = NewMovement;
}


