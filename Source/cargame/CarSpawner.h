// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "WhiteCar.h"
#include "Components/ArrowComponent.h"
#include "Math/UnrealMathUtility.h"
#include "CarSpawner.generated.h"

UCLASS()
class CARGAME_API ACarSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ACar>> AllCars;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	FHitResult Hit;
	FTimerHandle DestroyTemplateTimer;
	UPROPERTY(EditDefaultsOnly)
	FVector StartPos;

	UPROPERTY(EditDefaultsOnly)
	FVector EndPos;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> AllRoundTemplates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	TArray<USceneComponent*> SpawnPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CarSpawning")
	AActor* RoundTemplateActor;
	
public:	
	// Sets default values for this actor's properties
	ACarSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void HandleCarSpawning(int Round);
	void DestroyTemplate();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetGameSpeed(float NewSpeed);
	void HandleTemplate(int Round);
};
