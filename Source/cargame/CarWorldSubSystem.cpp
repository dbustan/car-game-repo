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

void UCarWorldSubSystem::OnLevelStart()
{
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Road"), FoundActors);
	ARoad* Road = Cast<ARoad>(FoundActors[0]);
	Spawn = Road->GetArrowComponent()->GetComponentTransform();
	
}
