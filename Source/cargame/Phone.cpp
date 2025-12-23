// Fill out your copyright notice in the Description page of Project Settings.


#include "Phone.h"

// Sets default values
APhone::APhone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhoneModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhoneModel"));
	PhoneModel->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APhone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhone::Interact() {
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("Whoaoaoaa")));
}
