// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Character/SGPlayer_Character.h"
#include "UObject/Interface.h"
#include "IPlayerInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPlayerInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONDRAWER_API IIPlayerInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Interact(ASGPlayer_Character* Player);

	
};
