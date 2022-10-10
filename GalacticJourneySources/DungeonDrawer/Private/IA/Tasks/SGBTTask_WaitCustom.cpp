// Fill out your copyright notice in the Description page of Project Settings.

#include "IA/Tasks/SGBTTask_WaitCustom.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Functions/BP_FunctionLib.h"

USGBTTask_WaitCustom::USGBTTask_WaitCustom(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Wait";
	bNotifyTick = true;
}

EBTNodeResult::Type USGBTTask_WaitCustom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	WaitTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(WaitSelector.SelectedKeyName);

	if(WaitTime ==0)
		WaitTime = 1;
	
	// TRACE("wating time : %f",WaitTime);
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	
	return EBTNodeResult::InProgress;
}

void USGBTTask_WaitCustom::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f || OwnerComp.GetBlackboardComponent()->GetValueAsBool(ForceEndWaitSelector.SelectedKeyName) == true)
	{
		// continue execution from this node
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ForceEndWaitSelector.SelectedKeyName,false);
		TRACE("End wait")
		MyMemory->RemainingWaitTime = 0;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

// FString USGBTTask_WaitCustom::GetStaticDescription() const
// {
// 	if (FMath::IsNearlyZero(RandomDeviation))
// 	{
// 		return FString::Printf(TEXT("%s: %.1fs"), *Super::GetStaticDescription(), WaitTime);
// 	}
// 	else
// 	{
// 		return FString::Printf(TEXT("%s: %.1f+-%.1fs"), *Super::GetStaticDescription(), WaitTime, RandomDeviation);
// 	}
// }

void USGBTTask_WaitCustom::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	if (MyMemory->RemainingWaitTime)
	{
		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(MyMemory->RemainingWaitTime)));
	}
}

uint16 USGBTTask_WaitCustom::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitTaskMemory);
}

#if WITH_EDITOR

FName USGBTTask_WaitCustom::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}

#endif	// WITH_EDITOR