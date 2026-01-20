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
	// if (RoundTemplateActor)
	// {
	// 	FVector TemplateLocation = RoundTemplateActor->GetActorLocation();
	// 	FVector NewLocation = FVector(TemplateLocation.X, GetActorLocation().Y, TemplateLocation.Z);
	// 	RoundTemplateActor->SetActorLocation(NewLocation);
	// }
}

void ACarSpawner::SetGameSpeed(float NewSpeed)
{
	
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


void ACarSpawner::HandleTemplate(int Round)
{
	TSubclassOf<AActor> CurrentRoundTemplate = AllRoundTemplates[Round-1];
	StartPos = this->GetActorLocation();
	EndPos = StartPos.DownVector * 1000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility)) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = NULL;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform TemplateTransform = FTransform(FRotator::ZeroRotator, Hit.Location);
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
				HandleCarSpawning(Round);
			}
		}
		
	}
	UE_LOG(LogTemp, Display, TEXT("Spawned Template"));
}

void ACarSpawner::HandleCarSpawning(int Round)
{
	for (USceneComponent* SpawnPoint : SpawnPoints)
	{
		if (Round < 3)
		{
			GetWorld()->SpawnActor<ACar>(AllCars[0], SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
		}
	}
	
	GetWorldTimerManager().SetTimer(DestroyTemplateTimer,this, &ACarSpawner::DestroyTemplate, 3.0, true);
	
	
}

void ACarSpawner::DestroyTemplate()
{
	// RoundTemplateActor->Destroy();
}
