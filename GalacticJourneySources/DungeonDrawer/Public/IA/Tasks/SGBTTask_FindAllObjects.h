// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SGBTTask_FindAllObjects.generated.h"

/**
 * 
 */
class UAISense_Hearing;

UCLASS()
class DUNGEONDRAWER_API USGBTTask_FindAllObjects : public UBTTaskNode
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
