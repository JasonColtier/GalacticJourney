// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/SGBTTask_CalculateObjectsUtility.h"

#include "Functions/BP_FunctionLib.h"
#include "Objets/SGObj_IAInteractible.h"
#include "IA/Controller/SGIASensor_Ctrl.h"

EBTNodeResult::Type USGBTTask_CalculateObjectsUtility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//je récupère le sensor de ma salle
	ASGIASensor_Ctrl* Sensor = Cast<ASGIASensor_Ctrl>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(BestSensorKey.SelectedKeyName));

	//if sensor valid
	if (Sensor && Sensor->AISensor_Pawn->AIInteracObjectsPawn.IsValidIndex(0))
	{
		ASGObj_IAInteractible* BestObject = FindBestObjectFromUtility(Sensor->AISensor_Pawn->AIInteracObjectsPawn,Sensor);

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BestObjectKey.SelectedKeyName, BestObject);

		TRACEIA(" best object : %s", *BestObject->GetName());

		return EBTNodeResult::Succeeded;
	}
	else
	{
		TRACEIA(" failed to calculate Objects utility");

		return EBTNodeResult::Failed;
	}
}

ASGObj_IAInteractible* USGBTTask_CalculateObjectsUtility::FindBestObjectFromUtility(
	TArray<ASGObj_IAInteractible*> UtilityObjectsArray, ASGIASensor_Ctrl* Sensor)
{
	//array des mailleurs sensors, Si plusieurs sensors ont la même valeur on fait un random dedans
	TArray<TPair<ASGObj_IAInteractible*, float>> BestObjects;

	BestObjects.Add(TPair<ASGObj_IAInteractible*, float>(UtilityObjectsArray[0], -300.f));

	// BestObjects.Add(TPairInitializer<T*,float>(UtilityObjectsArray[0],-100));//initialisation de la première valeur


	
	for (ASGObj_IAInteractible* object : UtilityObjectsArray)
	{
		if(!Sensor)
    		TRACEERROR("ERRROR SENSOR");
    		
		float currentObjectUtility = object->Ac_UtilityAI->CalculateUtilityScore(object,Sensor);

		if (currentObjectUtility > BestObjects[0].Value)
		{
			//si on a un nouveau meilleur sensor on supprime tous les anciens meilleurs
			BestObjects.Empty();

			BestObjects.Add(TPairInitializer<ASGObj_IAInteractible*, float>(object, currentObjectUtility));
			//initialisation de la première valeur

			//si un sensor a la même valeur que le meilleur actuel, on l'ajoute à l'array
		}
		else if (currentObjectUtility == BestObjects[0].Value)
		{
			BestObjects.Add(TPairInitializer<ASGObj_IAInteractible*, float>(object, currentObjectUtility));
		}
	}

	//random parmis les meilleurs sensors s'il y en a plusieurs avec la même valeur max
	int randomIndex = FMath::RandRange(0, BestObjects.Num() - 1);
	ASGObj_IAInteractible* RandomBest = BestObjects[randomIndex].Key;

	return RandomBest;
}