// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SGIA_Ctrl.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGIA_Ctrl : public AAIController
{
	GENERATED_BODY()

public:
	ASGIA_Ctrl() = default;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BT; 

	UPROPERTY()
	UBlackboardComponent* BB;

	UPROPERTY(EditAnywhere)
	FName isSensorKey = "IsSensor";

	virtual void OnPossess(APawn* InPawn) override;
	
};
