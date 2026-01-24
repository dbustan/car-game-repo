  #pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "PlayerCharacterHUD.Generated.h"

UCLASS(Abstract)
class CARGAME_API UPlayerCharacterHUD : public UUserWidget
{
  GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock * RoundTimerText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock * RoundNumBaseText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage * RoundEmojiInText;
	// UPROPERTY(EditAnywhere, meta = (BindWidget))
	// class UOverlay * RoundEmojiOverlay;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* RoundEmojiOverlay;
	UPROPERTY(VisibleAnywhere)
	class UCanvasPanelSlot* RoundEmojiCanvasSlot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoundStartUI")
	FVector2D RoundStartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoundStartUI")
	FVector2D RoundStartEndPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoundStartUI")
	float CurrentRoundSetupTimer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoundStartUI")
	TArray<UTexture*> RoundEmojis;
	bool CanRunAnim;
	float NormalizedAlpha;
	float MaxRoundSetupTimer;
	
	
  public:
	void SetRoundTime(FText RoundTime);
	void SetRound(FText RoundNum);
	void SetRoundNumBaseText(FText RoundNumBase);
	void SetRoundEmojiText(UImage* RoundEmoji);
	void RunRoundBaseAnimation();
	void SetRoundStartTimer(float NewTime);
	void InitialCastToMoveRoundEmoji();
	virtual void NativeTick ( const FGeometry& MyGeometry,
float InDeltaTime) override;
	

};

