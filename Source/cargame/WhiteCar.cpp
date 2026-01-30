// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteCar.h"

AWhiteCar::AWhiteCar() 
{
	
	PlayerDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerDetectionBox"));
	PlayerDetection->SetupAttachment(CarScene);
	PlayerDetection->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerDetection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
}

void AWhiteCar::BeginPlay()
{
    Super::BeginPlay();
	PlayerDetection->OnComponentBeginOverlap.AddDynamic(this, &AWhiteCar::OverlapBegin);
	Speed = 300.0f;
	
}

void AWhiteCar::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsGoingIn = ShouldHappen(45);
	if (IsGoingIn)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Going in"));
		RotateCar();
		GetWorldTimerManager().SetTimer(RotationTimer, this, &AWhiteCar::RotateCar, 0.3, false);
	}
}
bool AWhiteCar::ShouldHappen(int percentage)
{
	return (FMath::RandRange(1, 100/percentage)==1?true:false);
}

void AWhiteCar::RotateCar()
{
	RotationCount++;
	if (RotationCount <= 3)
	{
		FRotator NewRotation = FRotator(0, 10, 0);
		this->AddActorLocalRotation(NewRotation);
		if (RotationCount == 2)
		{
			Speed = 1000;
		}
		GetWorldTimerManager().SetTimer(RotationTimer, this, &AWhiteCar::RotateCar, 0.3, false);
	} 
	
	
}

void AWhiteCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	// FVector Location = GetActorLocation();
	// Location += GetActorForwardVector() * Speed * DeltaTime;
 //    SetActorLocation(Location);
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Location.ToString());
}




