// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objets/SGObj.h"
#include "IPlayerInteraction.h"
#include "Components/WidgetComponent.h"
#include "SGObj_ScreenGraviton.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_ScreenGraviton : public ASGObj, public IIPlayerInteraction
{
	GENERATED_BODY()

public:

	ASGObj_ScreenGraviton();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ControlPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* ControlWidget;

};
