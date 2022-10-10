// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <queue>


#include "GameFramework/GameState.h"
#include "IA/Pawn/SGIASensor_Pawn.h"
#include "Objets/SGObj_IAInteractible.h"
#include "Net/UnrealNetwork.h"
#include "Tuto/SGTutorialManager.h"


#include "SGGameState.generated.h"

class ASGIASensor_Ctrl;
class ASGObj_EnergyStock;
/**
 *
 */

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSensorsInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewUrgentTask, ASGObj_IAInteractible*, UrgentTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewTask, ASGObj_IAInteractible*, NewTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRepairedTask, ASGObj_IAInteractible*, ReopairedTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndGame, bool, victory);

UCLASS()
class DUNGEONDRAWER_API ASGGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASGGameState() = default;

	//la vie max du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Replicated,Category=ShipSettings)
	float MaxLife = 10;

	//la vie du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Replicated,Category=ShipSettings)
	float ShipLife = MaxLife;

	//la vie max du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Replicated,Category=ShipSettings)
	float MaxShipEnergy = 50;

	//la vie du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category=ShipSettings)
	float ShipEnergy = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=ShipSettings)
	USoundBase* SoundDamageToShip;
	
	UPROPERTY(EditAnywhere,Category=ShipSettings)
	float FixedDPSToShip = -0.1f;
	
	//à quel pourcentage de la vie du vaisseau on shutdown ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flow)
	float PercentageShutdown = 30;

	UPROPERTY(EditAnywhere,Category=Flow)
	float EnergyRequiredToFinishTuto = 10;

	UPROPERTY()
	int TimeTutoFinished = 0;
	
	UPROPERTY(Replicated)
	ASGObj_EnergyStock* EnergyStock;

	UPROPERTY(Replicated, BlueprintReadOnly)
	ASGTutorialManager* TutorialManager;

	//débug pour faire durer la partie longtemps !
	UPROPERTY(EditAnywhere, Category=Debug)
	bool DisableEndGame;

	//le switch se fait en bp
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeLightingScenario();
	
	//durée depuis le début de la partie, synchronisée entre les clients en théorie
	//utiliser la propriété ElapsedTime du game state pour récupérer le temps
	
	//Tous les controlleurs de sensor de la map
	//récupéré par le serveur et répliqué aux clients
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<ASGIASensor_Ctrl*> IASensorControllers;

	//Tous les controlleurs de sensor de la map
	//récupéré par le serveur et répliqué aux clients
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<ASGIASensor_Pawn*> IASensorPawns;

	

	UPROPERTY()
	TArray<ASGObj_IAInteractible*> DamagingActorsArray;

	//tableau avec les urgences actuelles
	std::deque<ASGObj_IAInteractible*> CurrentUrgencies;

	//nombre d'urgences depuis le début de la partie
	UPROPERTY()
	int TotalUrgenciesFromStart;
	
private:

	std::deque<ASGObj_IAInteractible*> QueueUrgentObjInteractible;


	
	UPROPERTY()
	TArray<ASGObj_IAInteractible*> ArrayActiveObjInteractible;

public:
	UFUNCTION(BlueprintCallable)
	ASGObj_IAInteractible* GetNextUrgentObjInteractible();

	UFUNCTION(BlueprintCallable)
	int GetNumberOfUrgentWainting();

	UFUNCTION(BlueprintCallable)
	TArray<ASGObj_IAInteractible*> GetArrayActiveObjInteractible() const { return ArrayActiveObjInteractible; }

	virtual void BeginPlay() override;

	//ajoute ou retire de la vie au vaisseau
	UFUNCTION(BlueprintCallable)
	void ModifyShipLife(float amount);

	UFUNCTION(BlueprintCallable)
    void ModifyShipEnergy(float amount);

	UFUNCTION()
	void Tick(float deltatime) override;

	UFUNCTION()
	void AddNewActiveTask(ASGObj_IAInteractible* ActiveTask);

	UFUNCTION()
	void AddNewUrgentTask(ASGObj_IAInteractible* UrgentTask);

	UFUNCTION()
	void RepairedTask(ASGObj_IAInteractible* RepairedTask);

	//delegate appelé quand on a récupéré tous les sensors
	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnSensorsInitialized OnSensorsInitialized;

	//delegate appelé quand on a une nouvelle tache URGENTE
	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnNewUrgentTask OnNewUrgentTask;

	//delegate appelé quand on a une nouvelle tache
	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnNewTask OnNewTask;

	//delegate appelé quand on a une nouvelle tache
	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnRepairedTask OnRepairedTask;

	//delegate appelé quand on a une nouvelle tache
	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnEndGame OnEndGame;

	//fin du jeu
	UFUNCTION(Server, Reliable)
    void ServerEndGame(bool victory);
	UFUNCTION(NetMulticast,Reliable)
    void MulticastEndGame(bool victory);

	bool DoOnceEndGame;
	bool DoOnceShutdown;
	
	// UFUNCTION(Server, Reliable)
 //    void ServerShutDown();
	// UFUNCTION(NetMulticast, Reliable)
	// void MulticastShutDown();

	UFUNCTION()
	void DoShutDown();
	
private:
	//récupération des sensors 3 sec après le début du jeu, à voir si on peut faire mieux peut être les spawner ?
	void GetAllSensorsAndPawns();

	UPROPERTY()
	bool DoOnceEndTuto;
};
