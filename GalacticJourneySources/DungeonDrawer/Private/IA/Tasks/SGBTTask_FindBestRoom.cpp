// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/SGBTTask_FindBestRoom.h"
#include "DrawDebugHelpers.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "IA/Controller/SGIAShip_Ctrl.h"

#define SensorPair ASGIASensor_Ctrl*,float

EBTNodeResult::Type USGBTTask_FindBestRoom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//tous les sensor de la map
	ASGIAShip_Ctrl* IAShip = Cast<ASGIAShip_Ctrl>(OwnerComp.GetAIOwner());

	if(!GameState)
		GameState = Cast<ASGGameState>(GetWorld()->GetGameState());

	TArray<ASGIASensor_Ctrl*> Sensors = GameState->IASensorControllers;


	if(Sensors.Num() == 0)
	{
		TRACESCREEN("no Sensor gotten from game state !")
		return EBTNodeResult::Failed;
	}
	
	ASGIASensor_Ctrl* BestSensor = FindBestObjectFromUtility(Sensors);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BestSensorKey.SelectedKeyName,BestSensor);

	TRACEIA("IA change room, new room : %s",*BestSensor->GetName());

	IAShip->OnChangeRoom.Broadcast(BestSensor);

	if(IAShip->bActivateDebuging)
	{
		DrawDebugLine(GetWorld(), BestSensor->GetPawn()->GetActorLocation(), IAShip->GetPawn()->GetActorLocation(),
                              FColor::Emerald,false,1);
		DrawDebugSphere(GetWorld(),BestSensor->GetPawn()->GetActorLocation(),50,12,FColor::Emerald,false,1.f);
	}

	//Le déplacement
	OwnerComp.GetAIOwner()->GetPawn()->SetActorLocation(BestSensor->GetPawn()->GetActorLocation());

	
	return EBTNodeResult::Succeeded;
}

ASGIASensor_Ctrl* USGBTTask_FindBestRoom::FindBestObjectFromUtility(
    TArray<ASGIASensor_Ctrl*> UtilityObjectsArray)
{
	//array des mailleurs sensors, Si plusieurs sensors ont la même valeur on fait un random dedans
	TArray<TPair<ASGIASensor_Ctrl*, float>> BestObjects;

	//initialisation de la première valeur
	BestObjects.Add(TPair<ASGIASensor_Ctrl*, float>(UtilityObjectsArray[0], -100.f));



	for (ASGIASensor_Ctrl* sensor : UtilityObjectsArray)
	{		
		float currentObjectUtility = sensor->Ac_UtilityAI->CalculateUtilityScore(sensor->GetPawn(),sensor);

		if (currentObjectUtility > BestObjects[0].Value)
		{
			//si on a un nouveau meilleur sensor on supprime tous les anciens meilleurs
			BestObjects.Empty();
 
			BestObjects.Add(TPairInitializer<ASGIASensor_Ctrl*, float>(sensor, currentObjectUtility));
			//initialisation de la première valeur

			//si un sensor a la même valeur que le meilleur actuel, on l'ajoute à l'array
		}
		else if (currentObjectUtility == BestObjects[0].Value)
		{
			BestObjects.Add(TPairInitializer<ASGIASensor_Ctrl*, float>(sensor, currentObjectUtility));
		}
	}

	//random parmis les meilleurs sensors s'il y en a plusieurs avec la même valeur max
	int randomIndex = FMath::RandRange(0, BestObjects.Num() - 1);
	ASGIASensor_Ctrl* RandomBest = BestObjects[randomIndex].Key;

	return RandomBest;
}
