// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGIA_Pawn.h"
#include "SGIASensor_Pawn.generated.h"

class ASGObj_IAInteractible;
/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGIASensor_Pawn : public ASGIA_Pawn
{
	GENERATED_BODY()

	public:
	//sur quel panel de lUI est ce que ça s'affihce
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SensorIndexInUI = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SensorName;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// UTexture2D* BGRoomtexture;

};
