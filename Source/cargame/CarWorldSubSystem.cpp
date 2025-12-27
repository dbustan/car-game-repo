// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWorldSubSystem.h"

void UCarWorldSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//This is how we link the world beginplay to our starting function
	UWorld* World = GetWorld();
	
	if (World) {
		//you need to pass a function address specifically to link OnWorldBeginPlay to Trigger OnLevelStart
		World->OnWorldBeginPlay.AddUObject(this, &UCarWorldSubSystem::OnLevelStart);
	}
	//Since you can't make a blueprint class of a subsystem we have to gather the road from our folder
	FString RoadPath = TEXT("/Game/BPs/BP_Road.BP_Road_C");
	RoadToSpawn = StaticLoadClass(AActor::StaticClass(), nullptr ,*RoadPath);
	if (!RoadToSpawn) {
		UE_LOG(LogTemp, Error, TEXT("Road failed to load"));
	}	
}

void UCarWorldSubSystem::Tick(float DeltaTime)
{
	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.Owner = nullptr;
	FVector ActorLocation = PlayerPawn->GetActorLocation();
	float SpawnDistance = (ActorLocation - Spawn.GetLocation()).Size();
	/*AActor* SpawnedActor = GetWorld()->SpawnActor<AInteractables>(PhoneToSpawn, FVector::ZeroVector, PhonePos->GetComponentRotation(), SpawnParams);*/
	UE_LOG(LogTemp, Warning, TEXT("%f"), SpawnDistance);
	if (SpawnDistance < 10000 && !RoadSpawned) {
		RoadSpawned = true;
		ARoad* Road = GetWorld()->SpawnActor<ARoad>(RoadToSpawn, Spawn, SpawnInfo);
		if (Road == NULL) {
			UE_LOG(LogTemp, Warning, TEXT("dada"));
		}
		else {
			Spawn = Road->GetArrowComponent()->GetComponentTransform();
			
		}
	}

}

void UCarWorldSubSystem::OnLevelStart()
{
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Road"), FoundActors);
	ARoad* Road = Cast<ARoad>(FoundActors[0]);
	Spawn = Road->GetArrowComponent()->GetComponentTransform();
	RoadSpawned = false;
}
