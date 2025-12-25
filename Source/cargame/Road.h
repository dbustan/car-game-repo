// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class CARGAME_API ARoad : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road")
	class UStaticMeshComponent* Cube;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road")
	class UStaticMeshComponent* Road;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road")
	class UArrowComponent* Arrow;
public:	
	// Sets default values for this actor's properties
	ARoad();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UArrowComponent* GetArrowComponent();

};
