#include "PlayerCharacterHUD.h"

#include "Components/TextBlock.h"

void UPlayerCharacterHUD::SetRoundTime(float RoundTime)
{
	UIText->SetText(FText::AsNumber(RoundTime));
}

void UPlayerCharacterHUD::SetRound(FString RoundNum)
{
	UIText->SetText(FText::FromString(RoundNum));
}
