// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services_Decorators/SGBTService_UpdateDifficulty.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionComponent.h"

void USGBTService_UpdateDifficulty::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!GameState)
	{
		GameState = Cast<ASGGameState>(GetWorld()->GetGameState());
		TRACE("No GS, setting one");
	}


	// TRACE("GameTimeDifficulty : %f",)

	CurrentDelayBeforeNextSabotage = DefaultTimeBeforeSabotage - GameTimeDifficulty() + UrgenciesDifficulty();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitSelector.SelectedKeyName, CurrentDelayBeforeNextSabotage);

	UrgenciesDifficulty();
}

float USGBTService_UpdateDifficulty::GameTimeDifficulty()
{
	float CurrentTime01 = UKismetMathLibrary::MapRangeClamped(GameState->ElapsedTime - GameState->TimeTutoFinished, 0,
	                                                          TimeToMaxDifficulty, 0, 1);

	// TRACE("map : %f",CurrentTime01);

	return DifficultyCurve->GetFloatValue(CurrentTime01) * MaxTimeReductionBeforeSabotage;
}

float USGBTService_UpdateDifficulty::UrgenciesDifficulty()
{
	// TRACE("UrgenciesNumber : %d",UrgenciesNumber)

	if (GameState->CurrentUrgencies.size() > UrgenciesNumToActivateSlow)
	{
		return UrgenciesSlowAmount;
	}
	return 0;
}
