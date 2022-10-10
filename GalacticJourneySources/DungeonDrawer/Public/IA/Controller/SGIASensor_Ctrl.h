// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGIA_Ctrl.h"
#include "Objets/SGEObjTypes.h"
#include "Engine/DataTable.h"
#include "IA/SGAC_UtilityAI.h"
#include "IA/Pawn/SGIASensor_Pawn.h"



#include "SGIASensor_Ctrl.generated.h"

/**
 *
 */
class ASGObj_IAInteractible;
class ASGPlayer_Character;
class USGIAUtility_Function;

UCLASS()
class DUNGEONDRAWER_API ASGIASensor_Ctrl : public ASGIA_Ctrl
{
	GENERATED_BODY()

public:
	ASGIASensor_Ctrl();
	
	virtual void OnPossess(APawn* InPawn) override;

	//Perception Component, permet de sens les joueurs et les objets interactifs
	UPROPERTY(EditAnywhere)
		UAIPerceptionComponent* SGAIPerception;

	// //Tous les objets interactifs à récupérer au begin play
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	TArray<ASGObj_IAInteractible*> AIInteracObjects;

	//tous les joueurs à récupérer dynamiquement s'ils entrent dans le rayon de detection
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ASGPlayer_Character*> Players;

	//set le pawn casté pour un accès plus facile si besoin par d'autres classes
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASGIASensor_Pawn* AISensor_Pawn;

	//le type de mon objet
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EObjTypes> EObjectType;

	//pour gérer les décisions de l'IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USGAC_UtilityAI* Ac_UtilityAI;

	//pour override in blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CalculateUtilityScore"))
    float ReceiveCalculateUtilityScore();
};
