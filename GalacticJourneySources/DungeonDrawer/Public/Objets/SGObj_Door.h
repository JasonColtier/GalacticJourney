// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGObj_IAInteractible.h"
#include "Components/WidgetComponent.h" 
#include "Objets/SGObj_IAInteractible.h"
#include "SGObj_Door.generated.h"


/**
 * 
 */


UCLASS()
class DUNGEONDRAWER_API ASGObj_Door : public ASGObj_IAInteractible
{
	GENERATED_BODY()

	ASGObj_Door();


	virtual void Tick(float DeltaSeconds) override;

protected:
	

};
