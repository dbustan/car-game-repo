// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Road.generated.h"

UCLASS()
class CARGAME_API ARoad : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road")
	class UStaticMeshComponent* Cube;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road")
	class USceneComponent* Road;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	class UArrowComponent* PlayerCheckArrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	class UArrowComponent* NextRoadArrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	class UBoxComponent* PlayerDetection;

	bool RoadSpawned = false;
	bool SelfDestructTimer = false;
public:	
	// Sets default values for this actor's properties
	ARoad();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	UArrowComponent* GetArrowComponent();

};
