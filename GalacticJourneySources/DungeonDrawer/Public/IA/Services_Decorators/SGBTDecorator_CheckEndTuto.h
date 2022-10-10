// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGGameState.h"
#include "BehaviorTree/BTDecorator.h"
#include "Tuto/SGTutorialManager.h"

#include "SGBTDecorator_CheckEndTuto.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API USGBTDecorator_CheckEndTuto : public UBTDecorator
{
	GENERATED_BODY()

public:


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
