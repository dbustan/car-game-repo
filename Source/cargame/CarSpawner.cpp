// Fill out your copyright notice in the Description page of Project Settings.


#include "CarSpawner.h"

// Sets default values
ACarSpawner::ACarSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACarSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentGameSpeed = 1;

	
}

// Called every frame
void ACarSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACarSpawner::SetGameSpeed(float NewSpeed)
{
	CurrentGameSpeed = NewSpeed;
}

void ACarSpawner::SpawnCar()
{
	UE_LOG(LogTemp, Warning, TEXT("Reaching Spawn car"));
	StartPos = this->GetActorLocation();
	EndPos = StartPos.DownVector * 1000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility)) {
		UE_LOG(LogTemp, Warning, TEXT("Reaching Spawn car"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = NULL;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform CarTransform = FTransform(FRotator::ZeroRotator, Hit.Location);
		ACar* SpawnedActor = GetWorld()->SpawnActor<ACar>(AllCars[0], CarTransform, SpawnParams);
		//Have data gathered from UWorldsubsystem regarding this
		/*SpawnedActor->PlayAnimation();*/
		SpawnedActor->InitSpawnProperties(CurrentGameSpeed);
	}
}

