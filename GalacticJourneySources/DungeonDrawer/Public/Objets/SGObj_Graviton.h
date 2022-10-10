// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlayerInteraction.h"
#include "Components/WidgetComponent.h"
#include "Objets/SGObj_IAInteractible.h"
#include "SGObj_Graviton.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_Graviton : public ASGObj_IAInteractible, public IIPlayerInteraction
{
	GENERATED_BODY()

public:

	ASGObj_Graviton();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BaseDownGraviton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BaseUpGraviton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SphereGraviton;
};
