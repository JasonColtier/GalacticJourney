// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "SGTutorialSteps.generated.h"


UENUM(Blueprintable)
enum ETutorialSteps
{
	TakingBattery		UMETA(DisplayName = "TakingBattery"),
    FixingMachines		UMETA(DisplayName = "FixingMachines"),
    EndTuto				UMETA(DisplayName = "EndTuto"),
};
