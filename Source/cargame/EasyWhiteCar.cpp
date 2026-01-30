// Fill out your copyright notice in the Description page of Project Settings.


#include "EasyWhiteCar.h"

void AEasyWhiteCar::BeginPlay()
{
	Super::BeginPlay();
	Speed = 300;
}

void AEasyWhiteCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Display, TEXT("%f"), Speed);
}

// void AEasyWhiteCar::RotateCar()
// {
// 	RotationCount++;
// 	if (RotationCount <= 3)
// 	{
// 		FRotator NewRotation = FRotator(0, 10, 0);
// 		this->AddActorLocalRotation(NewRotation);
// 		GetWorldTimerManager().SetTimer(RotationTimer, this, &AEasyWhiteCar::RotateCar, 0.5, false);
// 	} 
// }

void AEasyWhiteCar::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsGoingIn = ShouldHappen(10);
	if (IsGoingIn)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Going in"));
		RotateCar();
		GetWorldTimerManager().SetTimer(RotationTimer, this, &AEasyWhiteCar::RotateCar, 0.5, false);
	}
}
