// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services_Decorators/SGBTService_SearchPlayers.h"
#include "Character/SGPlayer_Character.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "Perception/AIPerceptionComponent.h"

void USGBTService_SearchPlayers::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ASGIASensor_Ctrl* sensor_ctrl = static_cast<ASGIASensor_Ctrl*>(OwnerComp.GetAIOwner());

	if (sensor_ctrl)
	{
		TArray<AActor*> perceivedActors;
		TArray<ASGPlayer_Character*> players;
		sensor_ctrl->GetAIPerceptionComponent()->GetKnownPerceivedActors(nullptr, perceivedActors);
		for (AActor* perceivedActor : perceivedActors)
		{
			if (perceivedActor->IsA(ASGPlayer_Character::StaticClass()))
			{
				players.AddUnique(static_cast<ASGPlayer_Character*>(perceivedActor));
			}
		}
		sensor_ctrl->Players = players;
	}
}
