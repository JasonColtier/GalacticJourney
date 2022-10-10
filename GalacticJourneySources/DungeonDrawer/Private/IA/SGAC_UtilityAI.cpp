// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/SGAC_UtilityAI.h"

#include "Functions/BP_FunctionLib.h"
#include "IA/UtilityFunctions/SGIAUtility_Function.h"

// Sets default values for this component's properties
USGAC_UtilityAI::USGAC_UtilityAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USGAC_UtilityAI::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ASGGameState>(GetWorld()->GetGameState());
	// ...
}


// Called every frame
void USGAC_UtilityAI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float USGAC_UtilityAI::CalculateUtilityScore(AActor* Actor,ASGIASensor_Ctrl* Sensor)
{
	if(!Sensor)
		TRACEERROR("ERRROR SENSOR");
	
	FinalUtility = 0;
	for (USGIAUtility_Function* UtilityFunction : InstancedFunctions)
	{
		FinalUtility += UtilityFunction->CalculateUtility(Actor, Sensor);
	}

	// TRACEIA("%s sensor utility is %f",*GetPawn()->GetName(),SensorFinalUtility);


	return FinalUtility;
}

