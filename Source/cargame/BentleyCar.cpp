// Fill out your copyright notice in the Description page of Project Settings.


#include "BentleyCar.h"

void ABentleyCar::BeginPlay()
{
	Super::BeginPlay();
	Speed = 500.0f;
	GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 5, false);
	
	// RotateCar();
	
}

void ABentleyCar::RotateCar()
{
	
	RotationCount++;
	FRotator NewRotation;
	if (RotationCount <= 8)
	{
		NewRotation = FRotator(0, -10, 0);
		this->AddActorLocalRotation(NewRotation);
		if (RotationCount == 8)
		{
			GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 0.4, false);
		} else
		{
			GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 0.1, false);
		}
	} else if (RotationCount > 8 && RotationCount <= 16)
	{
		NewRotation = FRotator(0, 10, 0);
		this->AddActorLocalRotation(NewRotation);
		if  (RotationCount == 16)
		{
			GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 2.2, false);
		} else
		{
			GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 0.1, false);
		}
	} else
	{
		RotationCount = 0;
		GetWorldTimerManager().SetTimer(RotationTimer, this, &ABentleyCar::RotateCar, 0.1, false);
	}
}

ABentleyCar::ABentleyCar()
{
	
}

void ABentleyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
