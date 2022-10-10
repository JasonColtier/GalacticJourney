// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API ASGGameMode : public AGameMode
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ChangeLevel();
};
