// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CarScene = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));
	CarScene->SetupAttachment(RootComponent);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CarScene);
	
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACar::InitSpawnProperties(float ActionSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("WHAT"));
}


