// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interactables.h"
#include "Phone.h"
#include "Engine/World.h"
#include "PlayerCharacter.generated.h"
UCLASS()
class CARGAME_API APlayerCharacter : public ACharacter
{
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class APlayerController* PlayerController;

	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* inputMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* SpeedUpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* SlowDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* MouseInteractionCheck;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerBike")
	class UStaticMeshComponent* MotorcycleBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerBike")
	class UStaticMeshComponent* MotorcycleWheel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionTraceDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FHitResult Hit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Phone")
	class USceneComponent* PhonePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 0;

	UPROPERTY(EditDefaultsOnly)
	//idk why its like this but this was the only way to spawn the phone
	TSubclassOf<class APhone> PhoneToSpawn;
public:
	
	APlayerCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpeedUp(const FInputActionValue& InputValue);
	AActor* SpawnPhone();
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetPlayerMaxSpeed(float CurrentGameSpeed);
};
