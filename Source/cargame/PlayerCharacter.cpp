// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhonePos = CreateDefaultSubobject<USceneComponent>(TEXT("Phone Pos"));
	MotorcycleBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorcycleBase"));
	MotorcycleWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorcycleWheel"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	DeathParticlesComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DeathParticles"));
	DeathParticlesComponent->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);
	MotorcycleBase->SetupAttachment(RootComponent);
	MotorcycleWheel->SetupAttachment(RootComponent);
	PhonePos->SetupAttachment(RootComponent);
}

AActor* APlayerCharacter::SpawnPhone() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AInteractables>(PhoneToSpawn, FVector::ZeroVector, PhonePos->GetComponentRotation(), SpawnParams);
	if (!SpawnedActor) {
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
	
	CharacterMovementComponent = GetCharacterMovement();
	DefaultSpeed = 200.0f;
	CharacterMovementComponent->MaxWalkSpeed = DefaultSpeed;
	MaxSpeed = 2000.0f;
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		WindowsGameInstance = Cast<UWindowsGameInstance>(GameInstance);
	}
	 WindowsGameInstance->PlaySound(SpeedSound, DefaultPlaybackSpeed);
	if (PlayerHUDBP)
	{
		PlayerHUD = CreateWidget<UPlayerCharacterHUD>(GetWorld()->GetFirstPlayerController(),PlayerHUDBP);
		PlayerHUD->AddToPlayerScreen();
		PlayerHUD->InitialCastToMoveRoundEmoji();
		PlayerHUD->SetRoundNumEmojiText(1);
		PlayerHUD->SetGameInstance(WindowsGameInstance);
		UpdateRoundStartTimerUI(3);
		StartRoundUITween();
	}
	PlayerController->bShowMouseCursor = false;
	PlayerController->bEnableClickEvents = false;
	/*SpawnPhone();*/
}




void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleInteractions();
	HandleDefaultMovement();
	GetViewportFocus();
	if (!GetViewportFocus() && !AltTabDetected)
	{
		HandlePauseInput();
		AltTabDetected = true;
	} else
	{
		AltTabDetected = false;
	}
	
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (APlayerController* pController = Cast<APlayerController>(Controller)) {
		PlayerController = pController;
		/*PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;*/

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(SpeedUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SpeedUp);
		EnhancedInputComponent->BindAction(SpeedUpAction, ETriggerEvent::Completed, this, &APlayerCharacter::ReturnToNormalSpeed);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::HandlePauseInput);
	}
}
void APlayerCharacter::SetPlayerMaxSpeed(float CurrentGameSpeed)
{
	MaxSpeed = MaxSpeed * CurrentGameSpeed;
}

void APlayerCharacter::SetCanMove(bool NewCanMove)
{
	CanMove = NewCanMove;
}

void APlayerCharacter::EnablePlayerMovement()
{
	CanMove = true;
	HasInput = false;
}

void APlayerCharacter::SetCurrentRoundUI(FText Round)
{
	PlayerHUD->SetRound(Round);
}

void APlayerCharacter::UpdateTimerUI(FText NewTime)
{
	PlayerHUD->SetRoundTimeLeft(NewTime);
}

void APlayerCharacter::UpdateRoundStartTimerUI(float NewTime)
{
	if (PlayerHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("it works?"));
		PlayerHUD->SetRoundStartTimer(NewTime);
	}
	
}

void APlayerCharacter::StartRoundUITween()
{
	if (PlayerHUD)
	{
		PlayerHUD->RunRoundBaseAnimation();
	}
	
}

void APlayerCharacter::ChangeRoundIcon(int Round)
{
	PlayerHUD->SetRoundNumEmojiText(Round);
}



void APlayerCharacter::SetUpGameOver()
{
	if (DeathParticlesComponent)
	{
		DeathParticlesComponent->SetActive(true);
	}
	PlayerHUD->ActivateGameOverScreen();
	UpdateTimerUI(FText::FromString("Game Over"));
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerLost = true;
}

void APlayerCharacter::SetUpWin()
{
	PlayerHUD->ActivateWinScreen();
	UpdateTimerUI(FText::FromString("You Win!"));
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
}


void APlayerCharacter::HandleInteractions()
{
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
		/*UE_LOG(LogTemp, Warning, TEXT("%s"), *test);*/
		AInteractables* InteractableObj = Cast<AInteractables>(Hit.GetActor());
		if (InteractableObj) {
			InteractableObj->Interact();
		}
	}
}

void APlayerCharacter::HandleDefaultMovement()
{
	if (CanMove)
	{
		if (!HasInput)
		{
			Acceleration -= GetWorld()->GetDeltaSeconds();
			Acceleration = FMath::Clamp(Acceleration, 0, 1);
			CharacterMovementComponent->MaxWalkSpeed = FMath::Lerp(DefaultSpeed, MaxSpeed, Acceleration);
			CurrentPlaybackSpeed = FMath::Lerp(DefaultPlaybackSpeed, MaxPlaybackSpeed, Acceleration);
			WindowsGameInstance->PlaySound(SpeedSound, CurrentPlaybackSpeed);
			AddMovementInput(GetActorForwardVector(), true);
			
			// UE_LOG(LogTemp, Warning, TEXT("%f: Max walk speed"), CharacterMovementComponent->MaxWalkSpeed);
		}
	}
	
}

bool APlayerCharacter::GetViewportFocus()
{
	if (GEngine)
	{
		bool isFocused = GEngine->GameViewport->Viewport->IsForegroundWindow();
		return isFocused;
	}
	return true;
}

void APlayerCharacter::HandlePauseInput()
{
	
	if (!PlayerLost)
	{
		if (IsPaused)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unpausing..."));
			IsPaused = false;
		
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pausing..."));
			IsPaused = true;
		
			// FInputModeGameAndUI InputMode;
		
			// PlayerController->SetInputMode(InputMode);
		}
		PlayerHUD->SetPaused(IsPaused);
		PlayerController->bShowMouseCursor = IsPaused;
		UGameplayStatics::SetGamePaused(GetWorld(), IsPaused);
	}
	
	
}

void APlayerCharacter::SpeedUp(const FInputActionValue& InputValue) {
	if (CanMove)
	{
		HasInput = true;
		Acceleration += GetWorld()->GetDeltaSeconds();
		Acceleration = FMath::Clamp(Acceleration, 0, 1);
		CharacterMovementComponent->MaxWalkSpeed = FMath::Lerp(DefaultSpeed, MaxSpeed, Acceleration);
		CurrentPlaybackSpeed = FMath::Lerp(DefaultPlaybackSpeed, MaxPlaybackSpeed, Acceleration);
		WindowsGameInstance->PlaySound(SpeedSound, CurrentPlaybackSpeed);
		AddMovementInput(GetActorForwardVector(), InputValue.Get<bool>());
	}
	
	// UE_LOG(LogTemp, Warning, TEXT("Speeding up - Current Walk speed %f"), CharacterMovementComponent->MaxWalkSpeed);
}

void APlayerCharacter::ReturnToNormalSpeed(const FInputActionValue& InputValue)
{
	if (CanMove)
	{
		HasInput = false;
	}
}






