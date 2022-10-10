// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlayerInteraction.h"
#include "Objets/SGObj.h"
#include "SGObj_VerminV2.generated.h"

class ASGObj_SpawnerVermin;

/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_VerminV2 : public ASGObj, public IIPlayerInteraction
{
	GENERATED_BODY()

public:

	ASGObj_VerminV2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SkeletalMeshRobot;

	UPROPERTY()
		ASGPlayer_Character* PlayerNear;

	UPROPERTY()
		bool IsLookedAt = false;

	UPROPERTY(BlueprintReadWrite)
		bool IsActivated = false;
	
	virtual void Tick(float DeltaTime) override;

	void Interact(ASGPlayer_Character* Player);
	virtual void Interact_Implementation(ASGPlayer_Character* Player) override;

	UFUNCTION(Server, Reliable)
		void SetOwnerVermineSpawnerServer(ASGPlayer_Character* Player);

	UFUNCTION(NetMulticast, Reliable)
		void SetOwnerVermineSpawnerMulticast(ASGPlayer_Character* Player);

	void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;



	UPROPERTY(Replicated, BlueprintReadWrite)
		ASGObj_SpawnerVermin* RefSpawner;

};


