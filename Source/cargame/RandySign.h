// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "RandySign.generated.h"

UCLASS()
class CARGAME_API ARandySign : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Text")
	TArray<UTextRenderComponent*> MainText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Text")
	UTextRenderComponent* UntilAtRandysText;
	FTimerHandle TextAnimationTimer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Text")
	int MainTextLetterCount = 13;
public:	
	// Sets default values for this actor's properties
	ARandySign();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MainTextAnimation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
