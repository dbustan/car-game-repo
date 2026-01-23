  #pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacterHUD.Generated.h"

UCLASS(Abstract)
class CARGAME_API UPlayerCharacterHUD : public UUserWidget
{
  GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock * UIText;
  public:
	void SetRoundTime(float RoundTime);
	void SetRound(FString RoundNum);
	
};

