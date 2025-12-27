// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWorldSubSystem.h"

void UCarWorldSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//This is how we link the world beginplay to our starting function
	UWorld* World = GetWorld();
	
	if (World) {
		//you need to pass a function address specifically
		World->OnWorldBeginPlay.AddUObject(this, &UCarWorldSubSystem::OnLevelStart);
	}

}

void UCarWorldSubSystem::Tick(float DeltaTime)
{
	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector ActorLocation = PlayerPawn->GetActorLocation();
	float SpawnDistance = (ActorLocation - Spawn.GetLocation()).Size();

	if (SpawnDistance < 300000) {
		/*GetWorld()->SpawnActor<ARoad>(Spawn, );*/
	}

}

void UCarWorldSubSystem::OnLevelStart()
{
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Road"), FoundActors);
	ARoad* Road = Cast<ARoad>(FoundActors[0]);
	Spawn = Road->GetArrowComponent()->GetComponentTransform();
	
}
