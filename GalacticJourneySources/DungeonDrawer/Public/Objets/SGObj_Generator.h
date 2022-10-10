// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlayerInteraction.h"
#include "SGObj_IAInteractible.h"
#include "Components/WidgetComponent.h" 
#include "SGObj_Generator.generated.h"


/**
 * 
 */


UCLASS()
class DUNGEONDRAWER_API ASGObj_Generator : public ASGObj_IAInteractible, public  IIPlayerInteraction
{
	GENERATED_BODY()

	ASGObj_Generator();


	virtual void Tick(float DeltaSeconds) override;
	

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GeneratorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GeneratorMeshWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedRotation = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SequenceIndex = 0;

};
