// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class CARGAME_API AMainMenu : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MyWidgetClass;
	
	UPROPERTY()
	UUserWidget* MyWidgetInstance;
public:	
	// Sets default values for this actor's properties
	AMainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
