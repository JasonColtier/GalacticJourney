// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/SGBTTask_FindAllObjects.h"
#include "DungeonDrawer/DungeonDrawer.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "Perception/AIPerceptionComponent.h"
#include "Objets/SGObj_IAInteractible.h"

EBTNodeResult::Type USGBTTask_FindAllObjects::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASGIASensor_Ctrl* sensor_ctrl = static_cast<ASGIASensor_Ctrl*>(OwnerComp.GetAIOwner());
	if (!sensor_ctrl)
		return EBTNodeResult::Failed;

	if (!sensor_ctrl->AISensor_Pawn->AIInteracObjectsPawn.IsValidIndex(0))
	{
		TArray<AActor*> perceivedActors;
		sensor_ctrl->GetAIPerceptionComponent()->GetKnownPerceivedActors(nullptr, perceivedActors);

		for (AActor* perceivedActor : perceivedActors)
		{
			if (perceivedActor->IsA(ASGObj_IAInteractible::StaticClass()))
			{
				//le pawn gère ça maintenant
				// sensor_ctrl->AIInteracObjects.AddUnique(static_cast<ASGObj_IAInteractible*>(perceivedActor));
				
				//test de mettre ces des données au pawn
				sensor_ctrl->AISensor_Pawn->AIInteracObjectsPawn.AddUnique(static_cast<ASGObj_IAInteractible*>(perceivedActor));
				Cast<ASGObj_IAInteractible>(perceivedActor)->MyAssociatedSensorPawn = sensor_ctrl->AISensor_Pawn;
			}
		}
	}

	return EBTNodeResult::Succeeded;
}
