// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGGameState.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"


#include "SGAC_UtilityAI.generated.h"


class USGIAUtility_Function;
class ASGIASensor_Ctrl;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONDRAWER_API USGAC_UtilityAI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USGAC_UtilityAI();

	//la datatable permet de set les paramètres globaux de tous les objets
	UPROPERTY(EditAnywhere, Category="_IA")
	UDataTable* IAParameters;

	//une fois que toutes les fonctions statiques ont retournées leur utilité, on set cette variable avec leurs sommes
	//c'est la valeur finale de "est ce que je dois faire une action sur cet objet" de 0 (non) à 100 (oui)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="_IA")
	float FinalUtility;

	//On instancie des objets pour contenir les fonctions et avec les paramètres définis dans la datatable
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="_IA")
	TArray<USGIAUtility_Function*> InstancedFunctions;

	//la date de la dernière fois que l'IA a intéragit avec cet objet
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="_IA")
	float LastIAAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ASGGameState* GameState;
	
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Je calcule l'utilité de mon objet = l'utilité de toutes les fonctions de mon objet
	UFUNCTION(BlueprintCallable)
    virtual float CalculateUtilityScore(AActor* Actor,ASGIASensor_Ctrl* Sensor);
};
