// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlayerInteraction.h"
#include "Objets/SGObj.h"
#include "SGObj_Pile.generated.h"

/**
 * 
 */

class ASGObj_EnergyStock;

UCLASS()
class DUNGEONDRAWER_API ASGObj_Pile : public ASGObj, public IIPlayerInteraction
{
	GENERATED_BODY()

public:

	ASGObj_Pile();

	void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;//le mesh de la pile

	UPROPERTY()
	ASGPlayer_Character* PlayerNear;

	UPROPERTY(EditAnywhere)
	USceneComponent* BottomPivotScene;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CylinderEnergy;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioSource;

	UPROPERTY(EditAnywhere)
	USoundBase* BatteryOnFloating;

	UPROPERTY(EditAnywhere)
	USoundBase* BatteryEnergyEmpty;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Server, Reliable)
	void ChangeEnergy(float change);

	UFUNCTION(BlueprintCallable,NetMulticast, Reliable)
	void MulticastChangeEnergy(float change);

	UFUNCTION()
	void SetOwnerNoSee(bool noSee);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	float MaxEnergy = 10;
	
	private:
	UPROPERTY()
	float TimerTick = 1;
};
