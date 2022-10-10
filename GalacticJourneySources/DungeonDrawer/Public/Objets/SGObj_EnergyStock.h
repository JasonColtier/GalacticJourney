// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlayerInteraction.h"
#include "SGObj_Pile.h"
#include "Objets/SGObj.h"
#include "SGGameState.h"
#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"

#include "SGObj_EnergyStock.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_EnergyStock : public ASGObj, public IIPlayerInteraction
{
	GENERATED_BODY()

	ASGObj_EnergyStock();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh; //le mesh de la pile

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Holder1; //le holder de la pile
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Holder2; //le holder de la pile
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Holder3; //le holder de la pile

	UPROPERTY(EditAnywhere)
	USceneComponent* PivotPoint1; //le root de la pile posée
	UPROPERTY(EditAnywhere)
	USceneComponent* PivotPoint2; //le root de la pile posée
	UPROPERTY(EditAnywhere)
	USceneComponent* PivotPoint3; //le root de la pile posée

	UPROPERTY(EditAnywhere)
	USpotLightComponent* SpotLight1;//lumière qui éclaire l'endroit où la pile doit être posée
	UPROPERTY(EditAnywhere)
	USpotLightComponent* SpotLight2;
	UPROPERTY(EditAnywhere)
	USpotLightComponent* SpotLight3;

	// UPROPERTY(EditAnywhere)
	// UAudioComponent* AudioSource;

	UPROPERTY(EditAnywhere)
	USoundBase* SoundPickupPile;

	UPROPERTY(EditAnywhere)
	USoundBase* SoundPutDownPile;
	

	UPROPERTY(EditAnywhere)
	float PileFloatIntensity = 0.5f;

	UPROPERTY(EditAnywhere)
	float PileFloatSpeed = 1;
	
	//est ce qu'un joueur est proche ?
	UPROPERTY(EditAnywhere)
	float DrainEnergyRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float SpotLightIntensity = 1000;
	
	//est ce qu'un joueur est proche ?
	UPROPERTY()
	ASGGameState* GameState;
	
	//est ce qu'un joueur est proche ?
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ASGPlayer_Character* PlayerNear;

	//quel mesh parmis ceux pouvant accueillir les piles est ce qu'on regarde actuellement ?
	UPROPERTY()
	UStaticMeshComponent* LookedAtMesh;

	//un array pour les holder des piles
	UPROPERTY()
	TArray<UStaticMeshComponent*> ArrayHolders;

	//un array pour les piles actuellement posées
	UPROPERTY(EditAnywhere)
	TArray<ASGObj_Pile*> ArrayPiles;

	//un array
	UPROPERTY(EditAnywhere)
	TArray<USceneComponent*> ArraySceneComponents;

	//un array
	UPROPERTY(EditAnywhere)
	TArray<ULightComponent*> ArraySpotComponents;
	
	//intéraction = ramasser la pile
	void Interact(ASGPlayer_Character* Player);
	virtual void Interact_Implementation(ASGPlayer_Character* Player) override;

	UFUNCTION(Server, Reliable)
	void DrainEnergyPile(float Deltatime);
	
	
	//poser la pile
	UFUNCTION(Server, Reliable)
	void ServerPutDown(ASGPlayer_Character* Player, int index);
	UFUNCTION(NetMulticast,Reliable)
    void ServerRPCPutDownPile(ASGPlayer_Character* Player, int index);

	//prendre une pile
	UFUNCTION(Server, Reliable)
	void ServerPickUp(ASGPlayer_Character* Player, int index);
	UFUNCTION(NetMulticast,Reliable)
	void MulticastPickUpPile(ASGPlayer_Character* Player, int index);



	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RotationSpeed = 60;
	
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult) override;

	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	UPROPERTY()
	float TimerTick = 0.5f;

	UPROPERTY()
	float DelayPutDownPickUp = 0.1f;

	UPROPERTY()
	float TimerPutDownPickUp;

	UPROPERTY()
	bool CanInteractiWithBattery;

	UPROPERTY()
	FVector OriginalPileLoc;
};
