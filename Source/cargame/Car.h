// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Car.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetHitSignature);
UCLASS()
class CARGAME_API ACar : public AActor
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	class USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	class USceneComponent* CarScene;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	UAnimSequence* IdleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car")
	UBoxComponent* CarCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoundStart")
	bool CanMove;
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTargetHitSignature OnTargetHit;
public:	
	// Sets default values for this actor's properties
	ACar();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void KillPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitSpawnProperties(float ActionSpeed);
	void MoveForward(float DeltaTime);
	void SetMoving(bool NewMovement);
};
