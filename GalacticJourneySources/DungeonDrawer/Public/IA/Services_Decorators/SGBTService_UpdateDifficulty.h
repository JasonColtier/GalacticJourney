// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGGameState.h"
#include "BehaviorTree/BTService.h"
#include "SGBTService_UpdateDifficulty.generated.h"

/**
 * 
 */

UCLASS()
class DUNGEONDRAWER_API USGBTService_UpdateDifficulty : public UBTService
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector WaitSelector;

	UPROPERTY()
	ASGGameState* GameState;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//temps en seconde avant d'atteindre la difficulté maximum
	UPROPERTY(EditAnywhere,Category=DefaultDifficulty)
	float DefaultTimeBeforeSabotage = 9;

	float CurrentDelayBeforeNextSabotage = 0;
	
	//temps en seconde avant d'atteindre la difficulté maximum
	UPROPERTY(EditAnywhere,Category=DifficultyOverTime)
	float TimeToMaxDifficulty = 5*60;

	//courbe pour ajuster la difficulté joliement
	UPROPERTY(EditAnywhere,Category=DifficultyOverTime)
	UCurveFloat* DifficultyCurve;

	//combien de seconde j'enlève au maximum (ex: à 10min de jeu on retire 2sec au wait before next sabotage)
	UPROPERTY(EditAnywhere,Category=DifficultyOverTime)
	float MaxTimeReductionBeforeSabotage;

	//le nombre idéal de taches en même temps
	UPROPERTY(EditAnywhere,Category=Tasks)
	int targetActiveTasksNumber = 3;

	//à partir de combien d'urgences on active un "bonus" qui rajoute du temps avant le prochain sabotage
	UPROPERTY(EditAnywhere, Category=Urgencies)
	int UrgenciesNumToActivateSlow = 3;

	UPROPERTY(EditAnywhere, Category="Urgencies")
	float UrgenciesSlowAmount = 10;
	
	UFUNCTION()
	float GameTimeDifficulty();

	UFUNCTION()
	float UrgenciesDifficulty();
};
