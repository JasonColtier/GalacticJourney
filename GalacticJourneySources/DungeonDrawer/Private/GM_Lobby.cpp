// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Lobby.h"
#include "DungeonDrawer/DungeonDrawerCharacter.h"
#include "Functions/BP_FunctionLib.h"
#include "Kismet/GameplayStatics.h"

AGM_Lobby::AGM_Lobby()
{
}

void AGM_Lobby::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    
    UE_LOG(LogTemp, Warning, TEXT(" new player connected : %s"), *NewPlayer->GetName());

    SpawnPlayer(NewPlayer);
}

void AGM_Lobby::SpawnPlayer(APlayerController* PlayerController)
{

    if (PlayerStartsArray.Num() == 0) //si on a pas encore récupéré les différents player starts
    {
        UBP_FunctionLib::FindAllActorsOfClass(GetWorld(), PlayerStartsArray);

        //on trie les spawnpoints par leur numéro de tag
        PlayerStartsArray.Sort([](const APlayerStart& LHS, const APlayerStart& RHS)  { return FCString::Atoi(*LHS.PlayerStartTag.ToString()) < FCString::Atoi(*RHS.PlayerStartTag.ToString()); });
    }

    FVector Location;
    FRotator Rotation(0.0f, 0.0f, 0.0f);
    FActorSpawnParameters SpawnInfo;

    //si on a de la place pour tous les joueurs
    if (PlayerStartsArray.IsValidIndex(NumberOfPlayers))
    {
        Location = PlayerStartsArray[NumberOfPlayers]->GetActorLocation();
    }
    else//sinon on les fait spawer à 0
    {
        Location = FVector().ZeroVector;
        UE_LOG(LogTemp,Error,TEXT(" No player start ! "));
    }
    if(HasAuthority())
    {
        ACharacter* Character = GetWorld()->SpawnActor<ACharacter>(BP_Character, Location, Rotation, SpawnInfo);
    
        PlayerController->Possess(Character);
    }


    NumberOfPlayers ++;
}

void AGM_Lobby::ChangeLevel_Implementation()
{
    ProcessServerTravel(MapLevelName,false);
}

