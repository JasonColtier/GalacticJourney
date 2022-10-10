// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "SGEObjTypes.generated.h"

//Note : enum des objets interactifs pour l'IA, modifiable à volonté 

UENUM(Blueprintable)
enum EObjTypes
{
	Door			UMETA(DisplayName = "Door"),
	Light			UMETA(DisplayName = "Light"),
	Gravity			UMETA(DisplayName = "Gravity"),
	Sensor			UMETA(DisplayName = "Sensor"),
	Breach			UMETA(DisplayName = "Breach"),
	Generator		UMETA(DisplayName = "Generator"),
	MotorPump		UMETA(DisplayName = "MotorPump"),
	Vermin			UMETA(DisplayName = "Vermin"),
	Graviton		UMETA(DisplayName = "Graviton"),
	ShipCore		UMETA(DisplayName = "ShipCore"),
	NotUsedForIA	UMETA(DisplayName = "NotUsedForIA"),
};
