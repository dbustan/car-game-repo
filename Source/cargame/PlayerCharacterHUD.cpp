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

void UPlayerCharacterHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CanRunAnim)
	{
		if (NormalizedAlpha > 0.0f)
		{
			FVector2D CurrentPos = FMath::Lerp(RoundStartEndPosition, RoundStartPosition, NormalizedAlpha);
			RoundEmojiCanvasSlot->SetPosition(CurrentPos);
			CurrentRoundSetupTimer -= InDeltaTime;
			NormalizedAlpha = FMath::Clamp(CurrentRoundSetupTimer/MaxRoundSetupTimer, 0.0f, 1.0f);
		}
	}
}




