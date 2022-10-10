// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Tasks/SGBTTask_DoBestObjectAction.h"

#include "DrawDebugHelpers.h"
#include "SGGameState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIAShip_Ctrl.h"
#include "Objets/SGObj_Door.h"
#include "Objets/SGObj_IAInteractible.h"

EBTNodeResult::Type USGBTTask_DoBestObjectAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ASGObj_IAInteractible* obj = Cast<ASGObj_IAInteractible>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BestObjectKey.SelectedKeyName));
	ASGIASensor_Ctrl* sensor = Cast<ASGIASensor_Ctrl>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BestSensorKey.SelectedKeyName));

	//si notre objet n'est pas déja saboté
	if(!obj->IsSabotaged)
	{

		if(obj->IgnoreIACooldown)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ForceEndWaitkey.SelectedKeyName,true);
			TRACE("force end wait true");
		}
		
		obj->ServerRPCDoAction();
		TRACESCREEN("Do action on %s",*obj->GetName())
	
        //je la date du dernier sabotage sur ce sensor
        sensor->Ac_UtilityAI->LastIAAction = Cast<ASGGameState>(GetWorld()->GetGameState())->ElapsedTime;
	
		ASGIAShip_Ctrl* IAShip = Cast<ASGIAShip_Ctrl>(OwnerComp.GetAIOwner());

		if(IAShip->bActivateDebuging)
		{
			DrawDebugLine(GetWorld(), obj->GetActorLocation(), IAShip->GetPawn()->GetActorLocation(),
                                  FColor::Green,false,1);
			DrawDebugSphere(GetWorld(),obj->GetActorLocation(),50,12,FColor::Green,false,1.f);
		}
	}
	
	
	return EBTNodeResult::Succeeded;
}
