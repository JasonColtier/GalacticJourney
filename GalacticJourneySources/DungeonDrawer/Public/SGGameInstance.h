// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine.h"

#include "SGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API USGGameInstance : public UGameInstance
{
	GENERATED_BODY()

	//Todo mettre en cpp ce qui marche en BP pour la création de session / le join ici

public:

	//Volume Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MusicVolume = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FXVolume = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GeneralVolume = 0.5f;

	//Control Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SensitivityX = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SensitivityY = 50.0f;
};
