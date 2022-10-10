// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/UtilityFunctions/SGIAUtility_Function.h"
#include "Kismet/KismetMathLibrary.h"

float USGIAUtility_Function::CalculateUtility(AActor* MyActor, ASGIASensor_Ctrl* Sensor)
{
	FunctionUtility = ReceiveCalculateUtility(MyActor, Sensor);//je récupère le résultat de ma fonction overridée en BP
	FunctionUtility = ClampUtility(FunctionUtility);//je remap et clamp avec le max de mon utility
	return FunctionUtility;
}

float USGIAUtility_Function::ClampUtility(float Utility)
{

	float ClampedUtility;
	if(WeightScore > 0)
	{		
		ClampedUtility=  UKismetMathLibrary::MapRangeClamped(Utility,0,100,0,WeightScore);
	}
	else
	{
		ClampedUtility = UKismetMathLibrary::MapRangeClamped(Utility,-100,0,WeightScore,0);
	}

	return ClampedUtility;
}

