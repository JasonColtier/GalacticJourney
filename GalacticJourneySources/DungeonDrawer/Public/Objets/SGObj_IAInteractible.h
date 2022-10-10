// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "IA/Pawn/SGIASensor_Pawn.h"
#include "Objets/SGObj.h"
#include "SGObj_IAInteractible.generated.h"


class USphereComponent;
class USGAC_UtilityAI;
class ASGIASensor_Ctrl;
class USGIAUtility_Function;
class ASGObj_IAInteractible;
class ASGPlayer_Character;
class ASG_PSRepeareTask;
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTaskRepaired, ASGObj_IAInteractible*, TaskRepaired,
                                             const TArray<ASGPlayer_Character*>&, Players);


UCLASS()
class DUNGEONDRAWER_API ASGObj_IAInteractible : public ASGObj
{
	GENERATED_BODY()

public:

	//pour faire des sons !
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	//
	// Les paramètres pour l'IA
	//

	//est ce que je suis déja saboté par l'IA ou pas ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_IA", Replicated)
	bool IsSabotaged = false;

	//la difficulté à réparer la tache associée à cet objet
	//1 = easy, 2 = moyen, 3 = hard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_IA")
	int SabotageDifficulty = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USGAC_UtilityAI* Ac_UtilityAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_IA", Replicated)
	bool HasBeenRepairedOnce = false;

	UPROPERTY(EditAnywhere,Category = "_IA")
	bool IgnoreIACooldown = false;

	//
	// Les dégats faits au ship
	//

	//temps en seconde avant de faire des dégats au vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Damages")
	float TimeUntilDamages = 60;

	//temps en seconde restant si on est saboté avant de faire des dégats au vaisseau
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "_Damages")
	float RemainingTimeUntilDamages = TimeUntilDamages;

	//dégats par seconde fait au vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Damages")
	float DPSToShip = -0.5;

	//% d'énergie de la pile donnée quand on réparer une machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnergyOnRepaired = 1;

	//
	// Params pour l'affichage dans l'UI
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_UI")
	bool ShowUpOnUI = true; //s'affiche sur l'UI ou pas (portes)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_UI")
	UTexture2D* IconeTaskActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_UI")
	UTexture2D* IconeTaskInactive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_UI")
	FText TaskDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "_UI", Replicated)
	ASGIASensor_Pawn* MyAssociatedSensorPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_UI")
	USoundBase* SoundRepaired;

	UPROPERTY()
	bool DoOnceAddUrgentTask = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reparation")
	TArray<UParticleSystemComponent*> ReparationParticle;

	UPROPERTY(EditAnywhere)
	float DurationParticleReparation = 1;

private:
	float TimerSeconds = 0;

	/*
	* FUNCTIONS
	*/

public:
	ASGObj_IAInteractible();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//cette fonction permet de checker 5sec après le début de la partie que notre objet a bien été repéré par son sensor :)
	UFUNCTION()
	void CheckRegisteredBySensor();

	//fonction répliquée pour faire l'action de mon objet
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	virtual void ServerRPCDoAction();

	//pour override in blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DoAction"))
	void ReceiveServerRPCDoAction();

	//sera appelé une fois la tache réparée
	UFUNCTION(BlueprintCallable)
	void Repaired(const TArray<ASGPlayer_Character*>& Players);

	//sera appelé une fois la tache réparée
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void MulticastRepaired(const TArray<ASGPlayer_Character*>& Players);

	UFUNCTION()
	void ReactivateCollision();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnTaskRepaired OnTaskRepaired;

	UFUNCTION()
	void DeactiveParticleRepeared();
};
