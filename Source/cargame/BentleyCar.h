// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "BentleyCar.generated.h"

/**
 * 
 */
UCLASS()
class CARGAME_API ABentleyCar : public ACar
{
	GENERATED_BODY()
protected:
	float RotationCount;
	FTimerHandle RotationTimer;
	float Speed;
	
protected:
	virtual void BeginPlay() override;
	void RotateCar();
public:
	// Called every frame
	ABentleyCar();
	virtual void Tick(float DeltaTime) override;\

};
