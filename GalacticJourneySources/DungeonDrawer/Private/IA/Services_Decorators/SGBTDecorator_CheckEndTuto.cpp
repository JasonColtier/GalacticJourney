// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Services_Decorators/SGBTDecorator_CheckEndTuto.h"

#include "Functions/BP_FunctionLib.h"


bool USGBTDecorator_CheckEndTuto::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//oui c'est pas fou dingue de faire un cast à chaque fois mais la fonction est const !
	//il faudrait trouver une autre fonction qui est appelée mais j'ai pas trouvé
	ASGGameState* GameState = Cast<ASGGameState>(GetWorld()->GetGameState());

	if(GameState->TutorialManager->CurrentTutorialStep == EndTuto)
		return true;
	
	return false;
}
