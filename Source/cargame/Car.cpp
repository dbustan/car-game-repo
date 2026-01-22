// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

#include "Components/BoxComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CarScene = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));
	CarScene->SetupAttachment(RootComponent);
	RoundEndCheck = CreateDefaultSubobject<UBoxComponent>(TEXT("RoundEndCheck"));
	RoundEndCheck->SetupAttachment(CarScene);
	RoundEndCheck->SetCollisionResponseToAllChannels(ECR_Ignore);
	RoundEndCheck->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	RoundEndCheck->Deactivate();
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CarScene);
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	CanMove = true;
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
		FVector Location = GetActorLocation();
		Location += GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(Location);
	}
}

void ACar::SetMoving(bool NewMovement)
{
	CanMove = NewMovement;
}


