// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SGBTService_SearchPlayers.generated.h"

/**
 * 
 */

UCLASS()
class DUNGEONDRAWER_API USGBTService_SearchPlayers : public UBTService
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
