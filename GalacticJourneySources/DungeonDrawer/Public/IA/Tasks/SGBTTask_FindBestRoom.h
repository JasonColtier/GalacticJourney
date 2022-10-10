// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGGameState.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SGBTTask_FindBestRoom.generated.h"

class ASGIASensor_Ctrl;
/**
 * 
 */
class UAISense_Hearing;

UCLASS()
class DUNGEONDRAWER_API USGBTTask_FindBestRoom : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BestSensorKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	ASGIASensor_Ctrl* FindBestObjectFromUtility(TArray<ASGIASensor_Ctrl*> UtilityObjectsArray);

	UPROPERTY()
	ASGGameState* GameState;
};
