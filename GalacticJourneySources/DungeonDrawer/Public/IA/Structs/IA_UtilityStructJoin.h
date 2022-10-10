// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "IA_UtilityStructFunction.h"
#include "Engine/UserDefinedStruct.h"
#include "Objets/SGEObjTypes.h"
#include "Engine/DataTable.h"
#include "IA_UtilityStructJoin.generated.h"

//Note cette structure est associée à un objet pour l'IA
//elle sert de paramètre pour définir quelles fonctions sont utilisées par l'objet

USTRUCT(BlueprintType)
struct FStructIA_UtilityJoin : public FTableRowBase
{
	
	GENERATED_BODY()

	//quel type d'objet je suis ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EObjTypes> Object;

	//quelles fonctions me permettent de prendre mes décisions ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStructIA_UtilityFunction> Functions;
};