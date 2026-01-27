	#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseHub.Generated.h"
UCLASS(Abstract)
class CARGAME_API UPauseHub : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UWidgetSwitcher* PauseHubSwitcher;
protected:
public:
	UFUNCTION(BlueprintCallable, Category="Hub")
	void ResetPauseHub();
};
