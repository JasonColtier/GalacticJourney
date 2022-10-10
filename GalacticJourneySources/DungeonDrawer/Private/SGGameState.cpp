// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameState.h"

#include "GeneratedCodeHelpers.h"
#include "Functions/BP_FunctionLib.h"
#include "IA/Controller/SGIAShip_Ctrl.h"
#include "IA/Pawn/SGIASensor_Pawn.h"
#include "Objets/SGObj_EnergyStock.h"
#include "Kismet/GameplayStatics.h"

ASGObj_IAInteractible* ASGGameState::GetNextUrgentObjInteractible()
{
	ASGObj_IAInteractible* out = nullptr;
	if (!QueueUrgentObjInteractible.empty())
	{
		out = QueueUrgentObjInteractible.back();
		QueueUrgentObjInteractible.pop_back();
	}
	return out;
}

int ASGGameState::GetNumberOfUrgentWainting()
{
	int i = 0;
	if (!QueueUrgentObjInteractible.empty())
	{
		i = QueueUrgentObjInteractible.size();
	}
	return i;
}


void ASGGameState::BeginPlay()
{
	Super::BeginPlay();

	//on met un delay le temps que les autres sensors soient possessed, il y a surement moyen de faire mieux
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ASGGameState::GetAllSensorsAndPawns, 3, false);
}

void ASGGameState::Tick(float deltatime)
{
	Super::Tick(deltatime);

	//cumul des taches pour les dégats
	// for (ASGObj_IAInteractible* damagingActor : DamagingActorsArray)
	// {
	// 	ModifyShipLife(damagingActor->DPSToShip*deltatime);	
	// }

	if (DamagingActorsArray.Num() > 0)
	{
		ModifyShipLife(FixedDPSToShip * deltatime);
	}

	if (EnergyStock)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (EnergyStock->ArrayPiles[i])
			{
				if (EnergyStock->ArrayPiles[i]->Energy > 0)
				{
					EnergyStock->ArrayPiles[i]->Energy -= EnergyStock->DrainEnergyRate * deltatime;
					if (EnergyStock->ArrayPiles[i]->GetOwner())
						EnergyStock->ArrayPiles[i]->ChangeEnergy(0);
					ModifyShipEnergy(EnergyStock->DrainEnergyRate * deltatime);
				}
			}
		}
	}

	if (ShipEnergy >= MaxShipEnergy)
		ServerEndGame(true);

	if (ShipLife <= 0)
		ServerEndGame(false);

	if (ShipLife <= MaxLife * PercentageShutdown / 100)
		DoShutDown();

	if (TutorialManager && !DoOnceEndTuto)
	{
		if (TutorialManager->CurrentTutorialStep == EndTuto)
		{
			DoOnceEndTuto = true;
			TimeTutoFinished = ElapsedTime;
			TRACE("finished tuto time : %d", TimeTutoFinished);
		}
	}
}

void ASGGameState::AddNewActiveTask(ASGObj_IAInteractible* ActiveTask)
{
	if (ActiveTask)
	{
		ArrayActiveObjInteractible.AddUnique(ActiveTask);
		OnNewTask.Broadcast(ActiveTask);
		TRACESCREEN("new active task : %s", *ActiveTask->GetName())
	}
}

void ASGGameState::AddNewUrgentTask(ASGObj_IAInteractible* UrgentTask)
{
	QueueUrgentObjInteractible.push_back(UrgentTask);
	// ArrayUrgentObjInteractible.AddUnique(UrgentTask);
	OnNewUrgentTask.Broadcast(UrgentTask);
	TRACESCREEN("new urgent task : %s", *UrgentTask->GetName())
	CurrentUrgencies.push_back(UrgentTask);
}

void ASGGameState::RepairedTask(ASGObj_IAInteractible* RepairedTask)
{
	OnRepairedTask.Broadcast(RepairedTask);
	ArrayActiveObjInteractible.Remove(RepairedTask);

	for (auto it = CurrentUrgencies.begin(); it != CurrentUrgencies.end(); ++it)
	{
		if (*it == RepairedTask)
		{
			TRACE("successfully removed item from urgent queue : %s", *RepairedTask->GetName())
			CurrentUrgencies.erase(it);
			return;
		}
	}

	for (auto it = QueueUrgentObjInteractible.begin(); it != QueueUrgentObjInteractible.end(); ++it)
	{
		if (*it == RepairedTask)
		{
			TRACE("successfully removed item from urgent queue : %s", *RepairedTask->GetName())
			QueueUrgentObjInteractible.erase(it);
			return;
		}
	}
}

void ASGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGGameState, IASensorControllers);
	DOREPLIFETIME(ASGGameState, IASensorPawns);
	DOREPLIFETIME(ASGGameState, MaxLife);
	DOREPLIFETIME(ASGGameState, ShipLife);
	DOREPLIFETIME(ASGGameState, MaxShipEnergy);
	DOREPLIFETIME(ASGGameState, ShipEnergy);
	DOREPLIFETIME(ASGGameState, EnergyStock);
	DOREPLIFETIME(ASGGameState, TutorialManager);
}


//permet de réduire la vie du vaisseau
void ASGGameState::ModifyShipLife(float amount)
{
	ShipLife += amount;

	if (ShipLife < 0)
		ShipLife = 0;

	if (ShipLife > MaxLife)
		ShipLife = MaxLife;

	// UGameplayStatics::SpawnSound2D(GetWorld(), SoundDamageToShip, 1);
}

//permet de réduire la vie du vaisseau
void ASGGameState::ModifyShipEnergy(float amount)
{
	ShipEnergy += amount;

	if (ShipEnergy < 0)
		ShipEnergy = 0;

	if (ShipEnergy > MaxShipEnergy)
		ShipEnergy = MaxShipEnergy;
}


void ASGGameState::GetAllSensorsAndPawns()
{
	UBP_FunctionLib::FindAllActorsOfClass(GetWorld(), IASensorControllers);

	TRACE("found %d sensors controller", IASensorControllers.Num());

	UBP_FunctionLib::FindAllActorsOfClass(GetWorld(), IASensorPawns);

	OnSensorsInitialized.Broadcast();
}


void ASGGameState::ServerEndGame_Implementation(bool victory)
{
	if (!DoOnceEndGame && !DisableEndGame)
	{
		DoOnceEndGame = true;
		MulticastEndGame(victory);
	}
}

void ASGGameState::MulticastEndGame_Implementation(bool victory)
{
	TRACE("end game, is victory ? : %hhd", victory);
	OnEndGame.Broadcast(victory);
}


void ASGGameState::DoShutDown()
{
	if (!DoOnceShutdown)
	{
		DoOnceShutdown = true;
		ChangeLightingScenario();
	}
}
