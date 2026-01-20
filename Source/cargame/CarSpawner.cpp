// Fill out your copyright notice in the Description page of Project Settings.


#include "CarSpawner.h"

#include "Components/SphereComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

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

void ACarSpawner::RoundHandling(int Round)
{
	switch (Round)
	{
		case 1:
			{
				HandleSpawning(Round);
			}
		break;
		default:
			{
				UE_LOG(LogTemp, Warning, TEXT("Sucks for you"));
			}
		
		break;
	}
	// StartPos = this->GetActorLocation();
	// EndPos = StartPos.DownVector * 1000;
	// if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility)) {
	// 	FActorSpawnParameters SpawnParams;
	// 	SpawnParams.Instigator = NULL;
	// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 	FTransform CarTransform = FTransform(FRotator::ZeroRotator, Hit.Location);
	// 	ACar* SpawnedActor = GetWorld()->SpawnActor<ACar>(AllCars[0], CarTransform, SpawnParams);
	// 	//Have data gathered from UWorldsubsystem regarding this
	// 	/*SpawnedActor->PlayAnimation();*/
	// 	SpawnedActor->InitSpawnProperties(CurrentGameSpeed);
	// }
}

void ACarSpawner::HandleSpawning(int Round)
{
	TSubclassOf<AActor> CurrentRoundTemplate = AllRoundTemplates[Round-1];
	StartPos = this->GetActorLocation();
	EndPos = StartPos.DownVector * 1000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility)) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = NULL;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform TemplateTransform = FTransform(FRotator::ZeroRotator, Hit.Location);
		if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(CurrentRoundTemplate, TemplateTransform, SpawnParams))
		{
			TArray<UArrowComponent*> Variations;
			SpawnedActor->GetComponents<UArrowComponent>(Variations);
			int Random = FMath::RandRange(0, Variations.Num() - 1);
			TArray<USceneComponent*> SpawnPoints;
			Variations[Random]->GetChildrenComponents(false, SpawnPoints);
			for (USceneComponent* SpawnPoint : SpawnPoints)
			{
				SpawnPoint->SetVisibility(true, true);
			}
			
			
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Spawned Template"));
}

