#include "PlayerCharacterHUD.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialExpressionOperator.h"

void UPlayerCharacterHUD::SetRoundTimeLeft(FText RoundTime)
{
	RoundTimerText->SetText(RoundTime);
}

void UPlayerCharacterHUD::SetRound(FText RoundNum)
{
	RoundTimerText->SetText(RoundNum);
}

void UPlayerCharacterHUD::SetRoundNumEmojiText(int RoundNum)
{
	
	CurrentRound = RoundNum;
	UE_LOG(LogTemp, Display, TEXT("Current Round: %d"),CurrentRound );
	RoundEmojiInText->SetBrushFromTexture(RoundEmojis[RoundNum]);
	RoundNumBaseText->SetText(FText::Format(INVTEXT("Round {0}"), RoundNum));
}

void UPlayerCharacterHUD::RunRoundBaseAnimation()
{
	CanRunAnim = true;
}

void UPlayerCharacterHUD::SetRoundStartTimer(float NewTime)
{
	CurrentRoundSetupTimer = NewTime;
	MaxRoundSetupTimer = NewTime;
	NormalizedAlpha = CurrentRoundSetupTimer/MaxRoundSetupTimer;
	
	if (CurrentRound > 1)
	{
		GameInstance->PlaySound(RoundWinSFX, 1.0f);
	}
	
}

 

void UPlayerCharacterHUD::InitialCastToMoveRoundEmoji()
{
	RoundEmojiCanvasSlot = Cast<UCanvasPanelSlot>(RoundEmojiOverlay->Slot);
	RoundStartPosition = RoundEmojiCanvasSlot->GetPosition();
	RoundStartEndPosition = FVector2D(RoundStartPosition.X * -1.5, RoundStartPosition.Y);
}

void UPlayerCharacterHUD::ActivateGameOverScreen()
{
	PlayAgainOverlay->SetVisibility(ESlateVisibility::Visible);
	ReturnToMainMenuOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerCharacterHUD::ActivateWinScreen()
{
	GameInstance->PlaySound(GameWinSFX, 1.0f);
	PlayAgainOverlay->SetVisibility(ESlateVisibility::Visible);
	ReturnToMainMenuOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerCharacterHUD::SetPaused(bool NewPaused)
{
	IsPaused = NewPaused;
	if (IsPaused)
	{
		PauseHub->SetVisibility(ESlateVisibility::Visible);
		
	} else
	{
		PauseHub->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerCharacterHUD::SetGameInstance(UWindowsGameInstance* GameInst)
{
	GameInstance = GameInst; 
}



void UPlayerCharacterHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CanRunAnim && !IsPaused)
	{
		if (NormalizedAlpha > 0.0f)
		{
			RoundEmojiOverlay->SetVisibility(ESlateVisibility::Visible);
			FVector2D CurrentPos = FMath::Lerp(RoundStartEndPosition, RoundStartPosition, NormalizedAlpha);
			RoundEmojiCanvasSlot->SetPosition(CurrentPos);
			CurrentRoundSetupTimer -= InDeltaTime;
			NormalizedAlpha = FMath::Clamp(CurrentRoundSetupTimer/MaxRoundSetupTimer, 0.0f, 1.0f);
		} else {
			RoundEmojiOverlay->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}




