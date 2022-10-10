// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SGBTTask_CalculateObjectsUtility.generated.h"

class ASGObj_IAInteractible;
class ASGIASensor_Ctrl;
/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API USGBTTask_CalculateObjectsUtility : public UBTTaskNode
{
	GENERATED_BODY()


public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BestSensorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BestObjectKey;

	UFUNCTION()
	ASGObj_IAInteractible* FindBestObjectFromUtility(TArray<ASGObj_IAInteractible*> UtilityObjectsArray,
	                                                 ASGIASensor_Ctrl* Sensor);
};
