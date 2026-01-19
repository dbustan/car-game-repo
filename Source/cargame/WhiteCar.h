// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "Components/BoxComponent.h"
#include "WhiteCar.generated.h"

/**
 * 
 */
UCLASS()
class CARGAME_API AWhiteCar : public ACar
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	class UBoxComponent* PlayerDetection;
	FTimerHandle RotationTimer;
	bool IsGoingIn;
	int RotationCount = 0;
public:
	// Sets default values for this actor's properties
	AWhiteCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool ShouldHappen(int percentage);
	void RotateCar();
	
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
