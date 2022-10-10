// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayer_Ctrl.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGPlayer_Ctrl : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* CharacterColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* FirstPersonneColor;

};
