// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGGameState.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "SGIAUtility_Function.generated.h"

/**
 * 
 */


UCLASS(Blueprintable)
class DUNGEONDRAWER_API USGIAUtility_Function : public UObject
{
	GENERATED_BODY()

public:

	//le score max de mon utilité. Si à la fin je retourne 50 et que mon WeightScore = 80 => final utility = 40
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeightScore = 100;

	//l'utilité finale de ma fonction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FunctionUtility = 0;

	//l'utilité finale de ma fonction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText FunctionDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> FunctionParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* Curve;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ASGGameState* GameState;
	
	//je calcule l'utilité de ma fonction
	UFUNCTION(BlueprintCallable)
	float CalculateUtility(AActor* MyActor, ASGIASensor_Ctrl* Sensor);

	//application du WeightScore
	UFUNCTION(BlueprintCallable)
	float ClampUtility(float Utility);

	//en BP
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CalculateUtility"))
	float ReceiveCalculateUtility(AActor* MyActor, ASGIASensor_Ctrl* Sensor);
};
