// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include  "Kismet/GameplayStatics.h"
#include "CarSpawner.h"
#include "Components/ArrowComponent.h"
#include "Subsystems/SubsystemCollection.h"
#include "CarWorldSubSystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CARGAME_API UCarWorldSubSystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
protected:
	FTransform Spawn;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACarSpawner> CarSpawnerBP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	class ACarSpawner* CarSpawnerActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	FVector CarSpawnerLocation = FVector(-240.0, 130.0, 170.0);
	/*TSubclassOf<class ARoad> RoadToSpawn;*/
	bool RoadSpawned;
public:

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//Everything here has to be inherited by a class to use FTickableGameObject
	//Code will not work unless you do
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return !IsTemplate(); }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UCarWorldSubSystem, STATGROUP_Tickables); }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	void OnLevelStart();
private: 
	void CarSpawnerInitialization();
};
