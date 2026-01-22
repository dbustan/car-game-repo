// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosCar.h"

AChaosCar::AChaosCar()
{
	
}

void AChaosCar::BeginPlay()
{
	Super::BeginPlay();
	Speed = 600.0f;
	RotationAmountLeft = 20;
	RotationAmountRight = 20;
	//Initialize Spawn in Period before Rotate car is initially called
	RotateCar();
};

void AChaosCar::RotateCar()
{
	RotationCount++;
	FRotator NewRotation;
	if (RotationCount <= RotationAmountLeft)
	{
		NewRotation = FRotator(0, -10, 0);
		this->AddActorLocalRotation(NewRotation);
	} else if (RotationCount <= RotationAmountRight)
	{
		NewRotation = FRotator(0, 10, 0);
		this->AddActorLocalRotation(NewRotation);
	} else
	{
		RotationCount = 0;
	}
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AChaosCar::RotateCar, 0.09, false);
}

void AChaosCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// FVector Location = GetActorLocation();
	// Location += GetActorForwardVector() * Speed * DeltaTime;
	// SetActorLocation(Location);
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Location.ToString());
}
