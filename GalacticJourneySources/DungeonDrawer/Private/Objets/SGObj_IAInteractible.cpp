// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_IAInteractible.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"
#include "SGGameState.h"
#include "Character/SGPlayer_Character.h"
#include "Components/SphereComponent.h"
#include "IA/Controller/SGIASensor_Ctrl.h"
#include "Functions/BP_FunctionLib.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Objets/SGObj_Pile.h"
#include "Perception/AISense_Hearing.h"
#include "Particles/ParticleSystemComponent.h"

ASGObj_IAInteractible::ASGObj_IAInteractible()
{
	Ac_UtilityAI = CreateDefaultSubobject<USGAC_UtilityAI>(TEXT("AC_UtilityAI"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	AudioComponent->SetupAttachment(SceneRootComponent);
}

void ASGObj_IAInteractible::BeginPlay()
{
	Super::BeginPlay();

	//si la datatable est bien set en bp
	if (Ac_UtilityAI->IAParameters)
	{
		UBP_FunctionLib::InitialiseUtilityFunctions(GetWorld(), Ac_UtilityAI->IAParameters, EObjectType, this,
		                                            Ac_UtilityAI->InstancedFunctions);
	}
	else
	{
		TRACESCREEN("Error : no IA Parameter set in AC_UtilityAI of %s", *GetNameSafe(this));
	}

	//je me fait connaitre auprès des sensors
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);

	GetComponents(ReparationParticle);

	for (auto particleSystem : ReparationParticle)
	{
		particleSystem->Deactivate();
	}

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ASGObj_IAInteractible::CheckRegisteredBySensor, 5, false);
}

void ASGObj_IAInteractible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSabotaged && ShowUpOnUI)
	{
		//temps restant avant de prendre des dégats = Date de la dernière action + Temps avant de prendre des dégats pour cette action - temps passé
		RemainingTimeUntilDamages = Ac_UtilityAI->LastIAAction + TimeUntilDamages - Ac_UtilityAI->GameState->
			ElapsedTime;

		//si il nous reste 1/3 du temps
		if (RemainingTimeUntilDamages < TimeUntilDamages * 0.3f)
		{
			if (!DoOnceAddUrgentTask)
			{
				DoOnceAddUrgentTask = true;
				Ac_UtilityAI->GameState->AddNewUrgentTask(this);
			}
			//si il nous reste plus de temps on commence à prendre des dégats toutes les secondes
			if (RemainingTimeUntilDamages < 0)
			{
				//on s'ajoute à l'array et c'est le GS qui va gérer ses propres dégats
				Ac_UtilityAI->GameState->DamagingActorsArray.AddUnique(this);
				// TRACESCREEN("Damage !");
			}
		}
	}
}


void ASGObj_IAInteractible::CheckRegisteredBySensor()
{
	if (!MyAssociatedSensorPawn)
	{
		TRACEERROR("ERROR ! i am not found by any sensor ! %s", *GetName())
		//	TRACESCREEN("ERROR ! i am not found by any sensor ! %s", *GetName())
		if (UBP_FunctionLib::IsEditor())
			DrawDebugSphere(GetWorld(), this->GetActorLocation(), 100, 50, FColor::Red, true);
	}
	else
	{
		if (GetWorld()->WorldType != EWorldType::Game && UBP_FunctionLib::IsEditor())
		{
			DrawDebugSphere(GetWorld(), this->GetActorLocation(), 100, 50, FColor::Green, false, 1);
			DrawDebugLine(GetWorld(), GetActorLocation(), MyAssociatedSensorPawn->GetActorLocation(), FColor::Green,
			              false, 1);
		}
	}
}

void ASGObj_IAInteractible::MulticastRepaired_Implementation(const TArray<ASGPlayer_Character*>& Players)
{
	// for (auto player : Players)
	// {
	// 	if (player)
	// 	{
	// 		TRACE("repaired by %s", *player->GetName())
	//            if (player->IsLocallyControlled())
	//            {
	//            	UGameplayStatics::SpawnSound2D(player, SoundRepaired, 1);
	//            	if (player->HoldedPile)
	//            	{
	//            		TRACE("changing energy of pile to %s", *player->GetName())
	//            		player->HoldedPile->ChangeEnergy(EnergyOnRepaired);
	//            		// player->HoldedPile->ChangeEnergy(EnergyOnRepairedPercent * (player->HoldedPile->MaxEnergy / 100));
	//            	}
	//            }
	//            	
	// 	}
	// }
	// HasBeenRepairedOnce = true;
	// IsSabotaged = false;
	// DoOnceAddUrgentTask = false;
	// OnTaskRepaired.Broadcast(this);
	// Ac_UtilityAI->GameState->RepairedTask(this);
	// //on se supprime de l'array
	// Ac_UtilityAI->GameState->DamagingActorsArray.Remove(this);
}

void ASGObj_IAInteractible::Repaired(const TArray<ASGPlayer_Character*>& Players)
{
	// TRACE("calling repaired on server");
	// MulticastRepaired(Players);

	for (auto player : Players)
	{
		if (player)
		{
			TRACE("repaired by %s", *player->GetName())
			if (player->IsLocallyControlled())
			{
				UGameplayStatics::SpawnSound2D(player, SoundRepaired, 1);
				player->LaunchSabotate();
				if (player->HoldedPile)
				{
					TRACE("changing energy of pile to %s", *player->GetName())
					player->HoldedPile->ChangeEnergy(EnergyOnRepaired);
					// player->HoldedPile->ChangeEnergy(EnergyOnRepairedPercent * (player->HoldedPile->MaxEnergy / 100));
				}
			}
		}
	}

	HasBeenRepairedOnce = true;
	IsSabotaged = false;
	DoOnceAddUrgentTask = false;
	OnTaskRepaired.Broadcast(this, Players);
	Ac_UtilityAI->GameState->RepairedTask(this);
	//on se supprime de l'array
	Ac_UtilityAI->GameState->DamagingActorsArray.Remove(this);

	for (auto* particleSysteme : ReparationParticle)
	{
		particleSysteme->Activate();
	}

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ASGObj_IAInteractible::DeactiveParticleRepeared, DurationParticleReparation, false);
}

void ASGObj_IAInteractible::ReactivateCollision()
{
	CapsuleCollider->Activate();
}

void ASGObj_IAInteractible::DeactiveParticleRepeared()
{
	for (auto particleSysteme : ReparationParticle)
	{
		particleSysteme->Deactivate();
	}
}


void ASGObj_IAInteractible::ServerRPCDoAction_Implementation()
{
	//si déja saboté on passe casse pas !
	if (IsSabotaged)
		return;

	if (ShowUpOnUI)
		Ac_UtilityAI->GameState->AddNewActiveTask(this);

	TRACE("done action on %s", *GetName());

	//on tente de désactiver / réactiver la capsule pour refresh l'event de collison
	CapsuleCollider->Deactivate();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ASGObj_IAInteractible::ReactivateCollision, 0.1f, false);

	//je récupère le temps depuis le début du jeu dans le game state à travers la propriété ElapsedTime qui existe de base dans le GameState
	Ac_UtilityAI->LastIAAction = Cast<ASGGameState>(GetWorld()->GetGameState())->ElapsedTime;
	// TRACESCREEN("LastIAAction set to %f",Ac_UtilityAI->LastIAAction)


	IsSabotaged = true;

	return ReceiveServerRPCDoAction();
}

void ASGObj_IAInteractible::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGObj_IAInteractible, IsSabotaged);
	DOREPLIFETIME(ASGObj_IAInteractible, MyAssociatedSensorPawn);
	DOREPLIFETIME(ASGObj_IAInteractible, HasBeenRepairedOnce);
}
