// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlayerInteraction.h"
#include "Objets/SGObj_IAInteractible.h"
#include "SGObj_Breachs.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_Breachs : public ASGObj_IAInteractible, public  IIPlayerInteraction
{
	GENERATED_BODY()

public:
	ASGObj_Breachs();

	virtual void BeginPlay() override;

	virtual void ServerRPCDoAction_Implementation() override;

	virtual void Tick(float DeltaSeconds) override;
	// virtual void PlayerInteraction() override;

	void Interact(ASGPlayer_Character* Player);
	virtual void Interact_Implementation(ASGPlayer_Character* Player) override;

	UFUNCTION(Server, Reliable)
		void RunOnServerBreach(int _listeIndex, ASGPlayer_Character* player);

	UFUNCTION(NetMulticast, Reliable)
		void RunOnClientBreah(int _listeIndex, ASGPlayer_Character* player);

	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintImplementableEvent)
		void ScrewMovement(UStaticMeshComponent* screw);

protected:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PlateMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ScrewMesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ScrewMesh2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ScrewMesh3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ScrewMesh4;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Breach;
	UPROPERTY(EditAnywhere)
		float DistanceToInteract;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BreachParticle;
	
	UPROPERTY(EditAnywhere)
		UMaterialInstance* TransparenceInstance;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* MetalInstance;

	UPROPERTY(EditAnywhere)
		USoundBase* BreachAparition;
	UPROPERTY(EditAnywhere)
		USoundBase* BreachWind;
	UPROPERTY(EditAnywhere)
		USoundBase* BreachPlate;
	UPROPERTY(EditAnywhere)
		USoundBase* BreachScrew;

	UPROPERTY()
		TArray<UStaticMeshComponent*> LMesh;

	UPROPERTY()
		int ListeIndex;

	UPROPERTY()
		bool FirstAction = true;
	UPROPERTY()
		bool FirstSabotage = true;
};
