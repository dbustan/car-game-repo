// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhonePos = CreateDefaultSubobject<USceneComponent>(TEXT("Phone Pos"));
	MotorcycleBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorcycleBase"));
	MotorcycleWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorcycleWheel"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	Camera->SetupAttachment(RootComponent);
	MotorcycleBase->SetupAttachment(RootComponent);
	MotorcycleWheel->SetupAttachment(RootComponent);
	PhonePos->SetupAttachment(RootComponent);

	
	
	
	

	/*Phone->SetupAttachment(RootComponent);*/
}

AActor* APlayerCharacter::SpawnPhone() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AInteractables>(PhoneToSpawn, FVector::ZeroVector, PhonePos->GetComponentRotation(), SpawnParams);
	if (SpawnedActor == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("WWOFAWD"));
	}
	SpawnedActor->AttachToComponent(PhonePos, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	FVector ScaleTest = FVector(0.05f, 0.05f, 0.05f);
	SpawnedActor->SetActorRelativeScale3D(ScaleTest);
	return SpawnedActor;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPhone();
}



// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MouseStartingPos;
	FVector WorldDirection;
	FVector EndLocation;
	PlayerController->DeprojectMousePositionToWorld(MouseStartingPos, WorldDirection);
	FVector StartPos = Camera->K2_GetComponentLocation();

	EndLocation = WorldDirection * 1000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndLocation, ECC_Visibility)) {
		/*DrawDebugLine(GetWorld(), StartPos, EndLocation, FColor::Red, false, 5.0f, 0, 3.0f);*/
		/*FString test = FString(Hit.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("%s"), *test));*/
		UE_LOG(LogTemp, Warning, TEXT("%s"), *test);
		AInteractables* InteractableObj = Cast<AInteractables>(Hit.GetActor());
		if (InteractableObj) {
			InteractableObj->Interact();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (APlayerController* pController = Cast<APlayerController>(Controller)) {
		PlayerController = pController;
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(inputMapping, 0);
			/*UE_LOG(LogTemp, Warning, TEXT("whow"));*/
		}
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		/*EnhancedInputComponent->BindAction(MouseInteractionCheck, ETriggerEvent::Triggered, this, &APlayerCharacter::InteractionCheck);*/

	}
}

void APlayerCharacter::Interact(const FInputActionValue& InputValue) {

	
}

void APlayerCharacter::InteractionCheck(const FInputActionValue& InputValue) {
	
	
}



