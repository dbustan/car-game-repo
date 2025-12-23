// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables.h"
#include "GameFramework/Actor.h"
#include "Phone.generated.h"

UCLASS()
class CARGAME_API APhone : public AInteractables
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Model")
	class UStaticMeshComponent* PhoneModel;
	
public:	
	// Sets default values for this actor's properties
	APhone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact() override;
};
