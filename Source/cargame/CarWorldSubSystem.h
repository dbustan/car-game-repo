// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Road.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include  "Kismet/GameplayStatics.h"
#include "FVector.h"
#include "Components/ArrowComponent.h"
#include "Subsystems/SubsystemCollection.h"
#include "CarWorldSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class CARGAME_API UCarWorldSubSystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
protected:
	FTransform Spawn;
public:

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	void OnLevelStart();
};
