// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Controller/SGIA_Ctrl.h"

#include "Functions/BP_FunctionLib.h"
#include "BehaviorTree/BehaviorTree.h"


void ASGIA_Ctrl::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	TRACE("Setting pawn")
    RunBehaviorTree(BT);
	Blackboard->InitializeBlackboard(*(BT->BlackboardAsset));
	BB = GetBlackboardComponent();

}
