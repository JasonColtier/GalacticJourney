// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGEObjTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "SGObj.generated.h"

UCLASS(Blueprintable)
class DUNGEONDRAWER_API ASGObj : public AActor
{
	GENERATED_BODY()



public:
	// Sets default values for this actor's properties
	ASGObj();


	//quel est le type de mon objet ??
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EObjTypes> EObjectType;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SceneRootComponent;

	UFUNCTION()
		virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
