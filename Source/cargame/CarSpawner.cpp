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
		DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Emerald, true, -1,  0, 10);
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
				SpawnPoint->SetVisibility(true, true);
				HandleCarSpawning(SpawnPoint,Round);
			}
			
		}
		
	}
	GetWorldTimerManager().SetTimer(DestroyTemplateTimer,this, &ACarSpawner::DestroyTemplate, 3.0, true);
}

void ACarSpawner::HandleCarSpawning(USceneComponent* SpawnPoint, int Round)
{
	// UE_LOG(LogTemp, Display, TEXT("Running"));
	ACar* CarActor;
	if (Round < 3)
	{
		CarActor = GetWorld()->SpawnActor<ACar>(AllCars[0], SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
		CurrentlySpawnedCars.Add(CarActor);
		CarActor->SetMoving(false);
	} else if (Round == 3)
	{
		
		CarActor = GetWorld()->SpawnActor<ACar>(AllCars[0], SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
		CurrentlySpawnedCars.Add(CarActor);
		CarActor->SetMoving(false);
	} else if (Round <= 6)
	{
		
	} else if (Round < 10)
	{
		
	} else if (Round == 10)
	{
		
	}
	if (SpawnPoint->ComponentHasTag("Last"))
	{
		LastCar = CarActor;
		UE_LOG(LogTemp, Error, TEXT("Last Car: %s"), *LastCar->GetName());
	}
	
	
}

ACar* ACarSpawner::GetLastCar()
{
	
	if (LastCar)
	{
		UE_LOG(LogTemp, Error, TEXT("Last Car %s"), *LastCar->GetName());
		return LastCar;
	} else
	{
		return nullptr;
	}
	
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
			Car->SetMoving(true);
		}
	}
}
