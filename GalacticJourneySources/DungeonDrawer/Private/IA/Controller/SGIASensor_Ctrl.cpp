// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Controller/SGIASensor_Ctrl.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIAShip_Ctrl.h"
#include "IA/Pawn/SGIASensor_Pawn.h"
#include "IA/Structs/IA_UtilityStructJoin.h"
#include "Perception/AIPerceptionComponent.h"
#include "Objets/SGObj_IAInteractible.h"

ASGIASensor_Ctrl::ASGIASensor_Ctrl()
{
	SGAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SGAIPerception"));
	Ac_UtilityAI = CreateDefaultSubobject<USGAC_UtilityAI>(TEXT("AC_UtilityAI"));
	SetPerceptionComponent(*SGAIPerception);
}

void ASGIASensor_Ctrl::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BB->SetValueAsBool(this->isSensorKey, true);

	
	AISensor_Pawn = Cast<ASGIASensor_Pawn>(InPawn);
	
	
	//si la datatable est bien set en bp
	if (Ac_UtilityAI->IAParameters)
	{
		UBP_FunctionLib::InitialiseUtilityFunctions(GetWorld(),Ac_UtilityAI->IAParameters,EObjectType,this,Ac_UtilityAI->InstancedFunctions);
	}
	else
	{
		TRACESCREEN("Error : no IA Parameter set ! in %s", *GetNameSafe(this));
	}
}
