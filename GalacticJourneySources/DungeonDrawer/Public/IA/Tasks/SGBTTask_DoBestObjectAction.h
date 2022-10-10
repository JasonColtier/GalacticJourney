// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SGBTTask_DoBestObjectAction.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API USGBTTask_DoBestObjectAction : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BestObjectKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BestSensorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ForceEndWaitkey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
