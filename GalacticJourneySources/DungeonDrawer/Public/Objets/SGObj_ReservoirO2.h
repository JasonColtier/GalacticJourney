// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objets/SGObj_IAInteractible.h"
#include "Objets/SGObj.h"
#include "IPlayerInteraction.h"
#include "SGObj_ReservoirO2.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_ReservoirO2 : public ASGObj, public IIPlayerInteraction
{
	GENERATED_BODY()
	
public:

	ASGObj_ReservoirO2();

	virtual void BeginPlay() override;


	void Interact(ASGPlayer_Character* Player);
	virtual void Interact_Implementation(ASGPlayer_Character* Player) override;

	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASGPlayer_Character* PlayerRef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
};
