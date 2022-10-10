// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGTutorialSteps.h"
#include "GameFramework/Actor.h"
#include "Objets/SGObj_IAInteractible.h"

#include "SGTutorialManager.generated.h"

class ASGGameState;
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewTutoStep, ETutorialSteps, newStep);


UCLASS()
class DUNGEONDRAWER_API ASGTutorialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGTutorialManager();

	UPROPERTY(EditAnywhere)
	TArray<ASGObj_IAInteractible*> ListActorsToSabotage;

	UPROPERTY()
	ASGObj_IAInteractible* CurrentActorSabotaged;


	UPROPERTY()
	ASGGameState* GameState;
	
	UFUNCTION()
	void DoNextSabotage(ASGObj_IAInteractible* RepairedObject);

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<ETutorialSteps>> AllTutoSteps;
	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ETutorialSteps> CurrentTutorialStep = TakingBattery;
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ValidateTutorialStep(ETutorialSteps step);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastValidateTutorialStep(ETutorialSteps step);

	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnNewTutoStep OnNewTutoStep;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	private:
	bool DoOnceBindDelegate = false;
};
