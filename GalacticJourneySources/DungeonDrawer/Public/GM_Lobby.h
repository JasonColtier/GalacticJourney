// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDRAWER_API AGM_Lobby : public AGameModeBase
{
    GENERATED_BODY()
    AGM_Lobby();

public:
    UPROPERTY()
    TArray<APlayerStart*> PlayerStartsArray;

    //le personnage à spawner !
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TSubclassOf<class ACharacter> BP_Character;

    UPROPERTY()
    int NumberOfPlayers = 0;

    UPROPERTY(EditAnywhere)
    FString MapLevelName = "MVP";

public:
    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION()
    void SpawnPlayer (APlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ChangeLevel();
};
