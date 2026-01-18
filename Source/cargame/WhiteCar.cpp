// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteCar.h"

AWhiteCar::AWhiteCar() : Super()
{
	
	PlayerDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerDetectionBox"));
	PlayerDetection->SetupAttachment(CarScene);

}

void AWhiteCar::BeginPlay()
{
    Super::BeginPlay();
    // 2. Tell the mesh to calculate its movement for 'zero' time 
    // This effectively "primes the pump" for the animation to start
    //SkeletalMesh->TickAnimation(0.0f, false);
    //SkeletalMesh->RefreshBoneTransforms();

    //// 3. Just in case it spawned in a 'paused' state
    //SkeletalMesh->bPauseAnims = false;
    //UE_LOG(LogTemp, Warning, TEXT("help"));
}

void AWhiteCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UAnimInstance* AnimInst = SkeletalMesh->GetAnimInstance();
    if (AnimInst)
    {
        float CurrentTime = AnimInst->GetWorld()->GetTimeSeconds();
        bool bIsPaused = SkeletalMesh->bPauseAnims;

        // Log every 1 second to avoid spam
        static float LogTimer = 0;
        LogTimer += DeltaTime;
        if (LogTimer >= 1.0f)
        {
            UE_LOG(LogTemp, Warning, TEXT("Car Anim Running: %s | Paused: %d"),
                *AnimInst->GetName(), bIsPaused);
            LogTimer = 0;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CRITICAL: No Anim Instance found on %s"), *GetName());
    }
}
