// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_SpawnerVermin.h"
#include "Net/UnrealNetwork.h"
//#include "Objets/"
#include <Runtime/Engine/Classes/Engine/Engine.h>

#include "Functions/BP_FunctionLib.h"


ASGObj_SpawnerVermin::ASGObj_SpawnerVermin()
{
	bReplicates = true;
}

void ASGObj_SpawnerVermin::BeginPlay()
{
	Super::BeginPlay();

	//spawn des vermines
	if (HasAuthority())
	{
		for (AActor* Spawnpoint : SpawnPointList)
		{
			ASGObj_VerminV2* Vermin = GetWorld()->SpawnActor<ASGObj_VerminV2>(
                VerminClass, Spawnpoint->GetActorLocation(), Spawnpoint->GetActorRotation());
			Vermin->RefSpawner = this;
			VerminList.Add(Vermin);
			DeactivateVermine(Vermin);
		}
	}
}

void ASGObj_SpawnerVermin::ServerRPCDoAction_Implementation()
{
	Super::ServerRPCDoAction_Implementation();


	ArrayPlayersRepair.Empty();
	for (ASGObj_VerminV2* Vermin : VerminList)
	{
		ActivateVermine(Vermin);
	}
	
}


void ASGObj_SpawnerVermin::MulticastRepair_Implementation()
{
	Repaired(ArrayPlayersRepair);
}


void ASGObj_SpawnerVermin::AddPlayerRepair_Implementation(ASGPlayer_Character* player)
{
	ArrayPlayersRepair.AddUnique(player);
}


void ASGObj_SpawnerVermin::RequestServerDestroy_Implementation(ASGObj_VerminV2* VerminV2)
{
	TRACESCREEN("DESTROY BY VERMIN SPAWNER SERVER")

	
		if (VerminList.Num() - 1 == 0)
		{
			MulticastRepair();
		}
	
	
	VerminV2->SkeletalMeshRobot->SetVisibility(false);
}




void ASGObj_SpawnerVermin::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGObj_SpawnerVermin, ArrayPlayersRepair);
	DOREPLIFETIME(ASGObj_SpawnerVermin, VerminList);
}
