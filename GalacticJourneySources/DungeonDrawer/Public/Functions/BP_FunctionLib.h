// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "DungeonDrawer/DungeonDrawer.h"
#include "Character/SGPlayer_Character.h"
#include "IA/Structs/IA_UtilityStructJoin.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_FunctionLib.generated.h"

//fonctions accessibles depuis tous les codes cpp et bp

UCLASS()
class DUNGEONDRAWER_API UBP_FunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static void FindAllActorsOfClass(UWorld* World, TArray<T*>& Out)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Find all "));

		for (TActorIterator<T> It(World); It; ++ It)
		{
			// AActor* Actor = Cast<AActor>(*It);
			// UE_LOG(LogTemp, Warning, TEXT("%s() : %s"), FUNC_NAME, *Actor->GetFName().ToString());
			Out.Add(*It);
		}
	};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsEditor() 
	{
#if WITH_EDITOR
		return true;
#else
		return false;
#endif
	}


	//raycast depuis la cam du joueur pour highlight l'objet pour lui
	UFUNCTION(BlueprintCallable)
	static UStaticMeshComponent* GetMeshLookedAtByPlayer(const ASGPlayer_Character* Player, const float Distance = 1000)
	{
		//Raycast
		FHitResult hitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(Player);
		UCameraComponent* playerCam = Player->GetFirstPersonCameraComponent();

		Player->GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
		                                             (playerCam->GetComponentLocation() + playerCam->GetForwardVector()
			                                             * Distance),
		                                             ECollisionChannel::ECC_Visibility);

		return Cast<UStaticMeshComponent>(hitResult.GetComponent());
	}

	//raycast depuis la cam du joueur pour highlight l'objet pour lui
	UFUNCTION(BlueprintCallable)
	static USkeletalMeshComponent* GetSkeletalMeshLookedAtByPlayerWithDistance(
		const ASGPlayer_Character* Player, const float Distance = 1000)
	{
		//Raycast
		FHitResult hitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(Player);
		UCameraComponent* playerCam = Player->GetFirstPersonCameraComponent();

		Player->GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
		                                             (playerCam->GetComponentLocation() + playerCam->GetForwardVector()
			                                             * Distance),
		                                             ECollisionChannel::ECC_Visibility);

		return Cast<USkeletalMeshComponent>(hitResult.GetComponent());
	}

	static void InitialiseUtilityFunctions(UWorld* World, UDataTable* IAParameters, TEnumAsByte<EObjTypes> EObjectType,
	                                       UObject* Self, TArray<USGIAUtility_Function*>& OutArray)
	{
		//je récupère un array de struct avec toutes les fonctions à instancier depuis la database
		TArray<FStructIA_UtilityJoin*> AllRows;
		FString Context = "";
		IAParameters->GetAllRows(Context, AllRows);

		for (FStructIA_UtilityJoin* Item : AllRows)
		{
			if (EObjectType.GetValue() == Item->Object.GetValue()) //objest est set en BP ici
			{
				for (FStructIA_UtilityFunction myFunc : Item->Functions) //toutes les fonctions à instancier
				{
					USGIAUtility_Function* MyObject = NewObject<USGIAUtility_Function>(Self, myFunc.FunctionClass);
					//je crée un object à partir de la fonction passée dans la datatable
					MyObject->WeightScore = myFunc.MaxWeight; //je set le score maw de cette fonction
					MyObject->FunctionDescription = myFunc.FunctionDesrciption;
					MyObject->GameState = Cast<ASGGameState>(World->GetGameState());
					MyObject->Curve = myFunc.OptionalCurve;
					//la description affichée à l'écran de débug
					for (FIA_UtilityStructFunctionParams param : myFunc.Parameters)
					{
						MyObject->FunctionParameters.Add(param.Parameter); //passé en paramètres à la fonction
					}
					OutArray.Add(MyObject); //et j'ajoute aux fonctions instancées
				}
			}
		}
	};
};
