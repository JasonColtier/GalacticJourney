// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Objets/SGEObjTypes.h"
#include "IA/UtilityFunctions/SGIAUtility_Function.h"
#include "IA_UtilityStructFunctionParams.generated.h"

//Note : un objet est caractérisé par un array de fonctions permettant de calculer l'utilité de cet objet

USTRUCT(BlueprintType)
struct FIA_UtilityStructFunctionParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ParameterDescription;

	//le score maximum de cette fonction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Parameter;
};