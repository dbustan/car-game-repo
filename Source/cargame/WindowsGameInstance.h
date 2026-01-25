// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WindowsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CARGAME_API UWindowsGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Audio")
	float CurrentMusicVolume;
	float CurrentSoundVolume;
public:
	UFUNCTION(BlueprintImplementableEvent, Category="Audio")
	void PlayMusic(float FadeOutOldSong, float FadeInNewSong, USoundBase* SoundToPlay);
};
