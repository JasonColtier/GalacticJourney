// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Controller/SGIAShip_Ctrl.h"
#include "IA/Pawn/SGIASensor_Pawn.h"
#include "Functions/BP_FunctionLib.h"



void ASGIAShip_Ctrl::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// TRACESCREEN("Ship IA Possessing pawn : %s",*InPawn->GetName())
	// TRACESCREEN("BB is : %s",*BB->GetName())

	//on met un delay le temps que les autres sensors soient possessed, il y a surement moyen de faire mieux
	// FTimerHandle UnusedHandle;
	// GetWorldTimerManager().SetTimer(
 //        UnusedHandle, this, &ASGIAShip_Ctrl::GetSensorsFromGameState, 1, false);

}

void ASGIAShip_Ctrl::BeginPlay()
{
	Super::BeginPlay();
}

// void ASGIAShip_Ctrl::GetSensorsFromGameState()
// {
// 	IASensorControllers = Cast<ASGGameState>(GetWorld()->GetGameState())->IASensorControllers;
// }
