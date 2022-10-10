// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGObj_IAInteractible.h"
#include "Objets/SGObj_IAInteractible.h"
#include "SGObj_Vermin.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_Vermin : public ASGObj_IAInteractible
{
	GENERATED_BODY()

public:
	ASGObj_Vermin();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// virtual void PlayerInteraction() override;
	// virtual void RunOnClients_Implementation() override;
	// virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	// virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
};
