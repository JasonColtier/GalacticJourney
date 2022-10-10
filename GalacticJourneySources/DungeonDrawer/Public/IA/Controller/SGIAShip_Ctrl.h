// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "SGIASensor_Ctrl.h"
#include "SGIA_Ctrl.h"
#include "SGIAShip_Ctrl.generated.h"

/**
 * 
 */

class ASGIASensor_Ctrl;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeRoom, ASGIASensor_Ctrl*, CurrentSensor);

UCLASS()
class DUNGEONDRAWER_API ASGIAShip_Ctrl : public ASGIA_Ctrl
{
	GENERATED_BODY()


public:
	virtual void OnPossess(APawn* InPawn) override;

	//tous les sensors de ma map et tous les endroits où on peut aller
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// TArray<ASGIASensor_Ctrl*> IASensorControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASGIASensor_Ctrl* CurrentRoomSensorController;

	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnChangeRoom OnChangeRoom;

	//set par le SGPlayer_Character et utilisé dans les tasks pour faire des prints
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivateDebuging;
	
protected:
	virtual void BeginPlay() override;

	// void GetSensorsFromGameState();
};
