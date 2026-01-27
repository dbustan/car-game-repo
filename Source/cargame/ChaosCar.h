// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "ChaosCar.generated.h"

/**
 * 
 */
UCLASS()
class CARGAME_API AChaosCar : public ACar
{
	GENERATED_BODY()
protected:
	int RotationCount;
	FTimerHandle RotationTimer;
	int RotationAmountLeft;
	int RotationAmountRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	USceneComponent* RootMovement;
	FVector ChaosLocation;
public:
	AChaosCar();
protected:
	virtual void BeginPlay() override;
	void RotateCar();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
