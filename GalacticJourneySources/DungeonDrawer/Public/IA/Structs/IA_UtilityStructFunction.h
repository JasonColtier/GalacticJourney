// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IA_UtilityStructFunctionParams.h"
#include "Engine/UserDefinedStruct.h"
#include "Objets/SGEObjTypes.h"
#include "IA/UtilityFunctions/SGIAUtility_Function.h"


#include "IA_UtilityStructFunction.generated.h"

//Note : un objet est caractérisé par un array de fonctions permettant de calculer l'utilité de cet objet

USTRUCT(BlueprintType)
struct FStructIA_UtilityFunction
{
	GENERATED_BODY()

	//une petite description de la fonction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText FunctionDesrciption;

	//la classe de la fonction, instanciée par les objets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USGIAUtility_Function> FunctionClass;

	//le score maximum de cette fonction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIA_UtilityStructFunctionParams> Parameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* OptionalCurve;
};