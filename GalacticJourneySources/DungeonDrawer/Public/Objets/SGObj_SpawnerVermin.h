// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "IPlayerInteraction.h"
#include "Objets/SGObj_IAInteractible.h"
#include "Objets/SGObj_VerminV2.h"
#include "SGObj_SpawnerVermin.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_SpawnerVermin : public ASGObj_IAInteractible, public  IIPlayerInteraction
{
	GENERATED_BODY()
	
public:
	ASGObj_SpawnerVermin();
	virtual void BeginPlay() override;
	

	virtual void ServerRPCDoAction_Implementation() override;

	UFUNCTION(Server,Reliable)
	void RequestServerDestroy(ASGObj_VerminV2* VerminV2);

	UFUNCTION(NetMulticast,Reliable)
	void MulticastRepair();

	UFUNCTION(BlueprintImplementableEvent)
	void Check();

	UFUNCTION(BlueprintImplementableEvent)
	void DeactivateVermine(ASGObj_VerminV2* VerminV2);

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateVermine(ASGObj_VerminV2* VerminV2);

	UPROPERTY()
	ASGObj_VerminV2* VerminToDestroy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnPointList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<ASGObj_VerminV2*> VerminList;

	UPROPERTY(BlueprintReadWrite,Replicated)
	TArray<ASGPlayer_Character* >ArrayPlayersRepair;
	
	UFUNCTION(Server,Reliable)
	void AddPlayerRepair(ASGPlayer_Character* player);
	
	UPROPERTY(EditAnywhere)
		TSubclassOf< ASGObj_VerminV2> VerminClass;

};
