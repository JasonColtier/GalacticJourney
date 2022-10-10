// Fill out your copyright notice in the Description page of Project Settings.


#include "Tuto/SGTutorialManager.h"

#include "SGGameState.h"
#include "Functions/BP_FunctionLib.h"

// Sets default values
ASGTutorialManager::ASGTutorialManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASGTutorialManager::DoNextSabotage(ASGObj_IAInteractible* RepairedObject)
{
	
	//on récupère le premier élément à saboter
	if (!CurrentActorSabotaged)
	{
		CurrentActorSabotaged = ListActorsToSabotage[0];
	}
	else
	{
		if (ListActorsToSabotage.IsValidIndex(ListActorsToSabotage.IndexOfByKey(RepairedObject) + 1))
		{
			CurrentActorSabotaged = ListActorsToSabotage[ListActorsToSabotage.IndexOfByKey(RepairedObject) + 1];
		}else
		{
			CurrentActorSabotaged = nullptr;
			ValidateTutorialStep(FixingMachines);
			GameState->OnRepairedTask.RemoveDynamic(this,&ASGTutorialManager::DoNextSabotage);
		}
	}

	if(CurrentActorSabotaged)
	{
		TRACETUTO(" Current sabotage = %s", *CurrentActorSabotaged->GetName());
		CurrentActorSabotaged->ServerRPCDoAction();
	}else
	{
		
		TRACETUTO(" no more sabotage");
	}
}

void ASGTutorialManager::ValidateTutorialStep_Implementation(ETutorialSteps step)
{
	MulticastValidateTutorialStep(step);
}

void ASGTutorialManager::MulticastValidateTutorialStep_Implementation(ETutorialSteps step)
{
	if (step == CurrentTutorialStep)
	{
		if (AllTutoSteps.IsValidIndex(AllTutoSteps.IndexOfByKey(step) + 1))
		{
			TRACETUTO("Validated tutorial step : %s", *UEnum::GetValueAsString(step));

			CurrentTutorialStep = AllTutoSteps[AllTutoSteps.IndexOfByKey(step) + 1];
			TRACETUTO("new step : %s", *UEnum::GetValueAsString(CurrentTutorialStep));

		}
	}

	if(CurrentTutorialStep == FixingMachines)
	{
		if(DoOnceBindDelegate == false)
		{
			DoOnceBindDelegate = true;
			GameState->OnRepairedTask.AddDynamic(this, &ASGTutorialManager::DoNextSabotage);
			DoNextSabotage(nullptr);
		}
	}
}

// Called when the game starts or when spawned
void ASGTutorialManager::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ASGGameState>(GetWorld()->GetGameState());
	GameState->TutorialManager = this;
}

// Called every frame
void ASGTutorialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
