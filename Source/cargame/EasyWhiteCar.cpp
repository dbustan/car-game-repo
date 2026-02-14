// Fill out your copyright notice in the Description page of Project Settings.


#include "EasyWhiteCar.h"


void AEasyWhiteCar::BeginPlay()
{
	Super::BeginPlay();
	Speed = 300;
	PercentageChance = 10;
	IsGoingIn = ShouldHappen(PercentageChance);
	TimeForInitialRotation = 0.5f;
}

void AEasyWhiteCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Display, TEXT("%f"), Speed);
}



