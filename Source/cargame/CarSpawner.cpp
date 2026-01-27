// Fill out your copyright notice in the Description page of Project Settings.


#include "CarSpawner.h"

#include "Components/SphereComponent.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

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
	
}



// Called every frame
void ACarSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




void ACarSpawner::HandleTemplate(int Round)
{
	TSubclassOf<AActor> CurrentRoundTemplate = AllRoundTemplates[Round-1];
	StartPos = this->GetActorLocation();
	EndPos = StartPos + StartPos.DownVector * 1000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility)) {
		// DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Emerald, true, -1,  0, 10);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = NULL;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform TemplateTransform = FTransform(FRotator::ZeroRotator, Hit.Location);
		UE_LOG(LogTemp, Error, TEXT("%s"), *Hit.Location.ToString());
		RoundTemplateActor = GetWorld()->SpawnActor<AActor>(CurrentRoundTemplate, TemplateTransform, SpawnParams);
		if (RoundTemplateActor)
		{
			TArray<UArrowComponent*> Variations;
			RoundTemplateActor->GetComponents<UArrowComponent>(Variations);
			int Random = FMath::RandRange(0, Variations.Num() - 1);
			Variations[Random]->GetChildrenComponents(false, SpawnPoints);
			for (USceneComponent* SpawnPoint : SpawnPoints)
			{
				// SpawnPoint->SetVisibility(true, true);
				HandleCarSpawning(SpawnPoint,Round);
			}
			
		}
		
	}
	GetWorldTimerManager().SetTimer(DestroyTemplateTimer,this, &ACarSpawner::DestroyTemplate, 3.0, true);
}

void ACarSpawner::HandleCarSpawning(USceneComponent* SpawnPoint, int Round)
{
	// UE_LOG(LogTemp, Display, TEXT("Running"));
	// if (!LevelConfigTable) return;
	//
	// FString RowNameString = FString::FromInt(Round);
	// FName RowName = FName(*RowNameString);
	// FLevelConfigRow* LevelData = LevelConfigTable->FindRow<FLevelConfigRow>(RowName, TEXT("Level Context"));
	ACar* CarActor = nullptr;
	TSubclassOf<ACar> CarChosen = nullptr;
	FName CarTag = SpawnPoint->ComponentTags[0];
	if (AllCarsMap.Contains(CarTag))
	{
		CarChosen = AllCarsMap[CarTag];
	} else
	{
		CarChosen = AllCarsMap["Bentley"];
	}
	
	if (CarChosen)
	{
		FVector CarLocation = SpawnPoint->GetComponentLocation();
		CarActor = GetWorld()->SpawnActor<ACar>(CarChosen, CarLocation, FRotator::ZeroRotator);
		CurrentlySpawnedCars.Add(CarActor);
		CarActor->SetMoving(false);
	}
	if (SpawnPoint->ComponentTags.Num() > 1)
	{
		if (CarActor)
		{
			LastCar = CarActor;
		} 
	}
	// if (LevelData)
	// {
	// 	TSubclassOf<ACar> CarChosen = ChooseCar(LevelData);
	// 	FVector Location;
	// 	if (CarChosen == AllCars[2] || CarChosen == AllCars[1])
	// 	{
	// 		Location = FVector(SpawnPoint->GetComponentLocation().X, SpawnPoint->GetComponentLocation().Y, SpawnPoint->GetComponentLocation().Z + BentChaosZOffset);
	// 	} else
	// 	{
	// 		Location = SpawnPoint->GetComponentLocation();
	// 	}
	// 	
	// 	CarActor = GetWorld()->SpawnActor<ACar>(CarChosen, Location, FRotator::ZeroRotator);
	// 	CurrentlySpawnedCars.Add(CarActor);
	// 	CarActor->SetMoving(false);
	// }
	// else
	// {
	// 	CarActor = nullptr;
	// 	UE_LOG(LogTemp, Error, TEXT("We done fucked up boy, Handle Car spawning doesn't work"));
	// }
	//
	// if (SpawnPoint->ComponentHasTag("Last"))
	// {
	// 	LastCar = CarActor;
	// 	UE_LOG(LogTemp, Error, TEXT("Last Car: %s"), *LastCar->GetName());
	// }
	
	
}

// TSubclassOf<ACar> ACarSpawner::ChooseCar(FLevelConfigRow* LevelData)
// {
// 	int TotalSum = 0;
// 	int AllCarsCount = AllCars.Num();
// 	for (int i = 0; i < AllCarsCount ; i++)
// 	{
// 		if (int32* CarWeight = LevelData->CarWeights.Find(AllCars[i]))
// 		{
// 			TotalSum += *CarWeight;
// 		}
// 	}
// 	int Rand = FMath::RandRange(0, TotalSum);
// 	for (int i = 0; i < AllCarsCount; i++)
// 	{
// 		if (int32* CarWeight = LevelData->CarWeights.Find(AllCars[i]))
// 		{
// 			if (Rand < *CarWeight)
// 			{
// 				return AllCars[i];
// 			}
// 			Rand -= *CarWeight;
// 		}
// 	}
// 	
// 	UE_LOG(LogTemp, Error, TEXT("Uh oh Choose Car CarSpawner does not work"));
// 	return AllCars[2];
// 	
// }

ACar* ACarSpawner::GetLastCar()
{
	
	if (LastCar)
	{
		UE_LOG(LogTemp, Error, TEXT("Last Car: %s"), *LastCar->GetName());
		return LastCar;
	} 
	return nullptr;
}

void ACarSpawner::DestroyAllInfo()
{
	for (ACar* Car : CurrentlySpawnedCars)
	{
		if (Car)
		{
			Car->Destroy();
		}
	}
	LastCar = nullptr;
	CurrentlySpawnedCars.Empty();
	// for (USceneComponent* SpawnPoint : SpawnPoints)
	// {
	// 	UE::MovieScene::ERunnerFlushState::Spawn
	// }
}


void ACarSpawner::DestroyTemplate()
{
	if (RoundTemplateActor)
	{
		RoundTemplateActor->Destroy();
	}
	
}



void ACarSpawner::StartCarMovement()
{
	for (ACar* Car : CurrentlySpawnedCars)
	{
		if (Car)
		{
			// UE_LOG(LogTemp, Error, TEXT(" %s"), *Car->GetName());
			Car->SetMoving(true);
		}
	}
}

TArray<ACar*> ACarSpawner::GetAllCarsSpawned()
{
	return CurrentlySpawnedCars;
}
