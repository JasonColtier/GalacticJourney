// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "SGBTTask_WaitCustom.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API USGBTTask_WaitCustom : public UBTTaskNode
{

	GENERATED_UCLASS_BODY()

	public:
    /** wait time in seconds */
 //    UPROPERTY(Category = Wait, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	// float ;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector WaitSelector;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ForceEndWaitSelector;

	UPROPERTY()
	float WaitTime = 1;
	
	/** allows adding random time to wait time */
	UPROPERTY(Category = Wait, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
	float RandomDeviation;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	// virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR

	protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};


