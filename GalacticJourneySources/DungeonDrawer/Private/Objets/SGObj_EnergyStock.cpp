// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_EnergyStock.h"

#include "Functions/BP_FunctionLib.h"
#include "Kismet/GameplayStatics.h"

ASGObj_EnergyStock::ASGObj_EnergyStock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");


	Holder1 = CreateDefaultSubobject<UStaticMeshComponent>("Holder1");
	Holder2 = CreateDefaultSubobject<UStaticMeshComponent>("Holder2");
	Holder3 = CreateDefaultSubobject<UStaticMeshComponent>("Holder3");
	PivotPoint1 = CreateDefaultSubobject<USceneComponent>("PivotPoint1");
	PivotPoint2 = CreateDefaultSubobject<USceneComponent>("PivotPoint2");
	PivotPoint3 = CreateDefaultSubobject<USceneComponent>("PivotPoint3");
	SpotLight1 = CreateDefaultSubobject<USpotLightComponent>("SpotLight1");
	SpotLight2 = CreateDefaultSubobject<USpotLightComponent>("SpotLight2");
	SpotLight3 = CreateDefaultSubobject<USpotLightComponent>("SpotLight3");
	// AudioSource = CreateDefaultSubobject<UAudioComponent>("AudioSource");

	Mesh->SetupAttachment(SceneRootComponent);
	Holder1->SetupAttachment(Mesh);
	Holder2->SetupAttachment(Mesh);
	Holder3->SetupAttachment(Mesh);
	PivotPoint1->SetupAttachment(Mesh);
	PivotPoint2->SetupAttachment(Mesh);
	PivotPoint3->SetupAttachment(Mesh);
	SpotLight1->SetupAttachment(Mesh);
	SpotLight2->SetupAttachment(Mesh);
	SpotLight3->SetupAttachment(Mesh);
	// AudioSource->SetupAttachment(Mesh);
}

void ASGObj_EnergyStock::BeginPlay()
{
	Super::BeginPlay();

	ArrayHolders = {Holder1, Holder2, Holder3};
	ArraySceneComponents = {PivotPoint1, PivotPoint2, PivotPoint3};
	ArraySpotComponents = {SpotLight1, SpotLight2, SpotLight3};
	GameState = Cast<ASGGameState>(GetWorld()->GetGameState());
	GameState->EnergyStock = this;
	OriginalPileLoc = PivotPoint1->GetComponentLocation();
}

void ASGObj_EnergyStock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerNear)
	{
		//on check toutes les x secondes pour évider un cast trop fréquent
		TimerTick += DeltaTime;
		if (TimerTick > 0.5f)
		{
			TimerTick = 0;
			LookedAtMesh = UBP_FunctionLib::GetMeshLookedAtByPlayer(PlayerNear);

			// if (LookedAtMesh)
			// TRACE("Looked mesh : %s", *LookedAtMesh->GetName())

			//pour chaque emplacement de pile
			for (int i = 0; i < 3; ++i)
			{
				//je réinitialise le highlight à 0
				ArrayHolders[i]->SetRenderCustomDepth(false);

				//aussi 0 pour les piles
				if (ArrayPiles[i])
				{
					ArrayPiles[i]->Mesh->SetRenderCustomDepth(false);
				}

				//si on regarde un des holder
				if (LookedAtMesh == ArrayHolders[i])
				{
					//si on a pas de pille alors je hightlight la pile qu'on peut prendre
					if (ArrayPiles[i] && !PlayerNear->HoldedPile)
					{
						ArrayPiles[i]->Mesh->SetRenderCustomDepth(true);
					}
						//sinon je highlight le holder pour qu'on la dépose
					else if (!ArrayPiles[i])
					{
						ArrayHolders[i]->SetRenderCustomDepth(true);
					}
				}
			}
		}
	}
	else //si on colide pas je reset tout
	{
		TimerTick = 1;
		for (int i = 0; i < 3; ++i)
		{
			ArrayHolders[i]->SetRenderCustomDepth(false);
			if (ArrayPiles[i])
				ArrayPiles[i]->Mesh->SetRenderCustomDepth(false);
		}
	}

	//check peu importe si un joueur est là ou pas
	//je fais tourner les piles si elles sont là et je les décharge
	for (int i = 0; i < 3; ++i)
	{
		if (ArrayPiles[i])
		{
			//on fait tourner la pile si elle a de l'énergie
			if (ArrayPiles[i]->Energy > 0)
			{
				ArrayPiles[i]->AddActorLocalRotation(FRotator(0, DeltaTime * RotationSpeed, 0));

				
				// //si au moins une pile a de l'énergie, je joue le son de charge
				// if(!AudioSource->IsPlaying())
				// {
				// 	AudioSource->Play();
				// }
			}
			else
			{
				
			}
			ArraySpotComponents[i]->SetIntensity(SpotLightIntensity);

			//on fait floter la pile 
			float offset = FMath::Cos(GetWorld()->GetTimeSeconds()*PileFloatSpeed);
			offset*=PileFloatIntensity;
			ArrayPiles[i]->SetActorLocation(FVector(ArrayPiles[i]->GetActorLocation().X,ArrayPiles[i]->GetActorLocation().Y,OriginalPileLoc.Z+offset));
		}
		else
		{
			ArraySpotComponents[i]->SetIntensity(SpotLightIntensity/10);
		}
	}
}


void ASGObj_EnergyStock::Interact_Implementation(ASGPlayer_Character* Player)
{
	LookedAtMesh = UBP_FunctionLib::GetMeshLookedAtByPlayer(Player);

	// if(TimerPutDownPickUp < DelayPutDownPickUp)
	// 	return;
	//
	// HasInteractedWithBattery = true;
	
	if (LookedAtMesh)
	TRACE(" interact with energy stock ! %s", *LookedAtMesh->GetName());

	//si on porte une pile alors on veut la poser
	if (Player->HoldedPile)
	{
		for (int i = 0; i < 3; ++i)
		{
			//je cherche le holder qu'on regarde
			if (LookedAtMesh == ArrayHolders[i] && !ArrayPiles[i])
			{
				//pose
				ServerPutDown(Player, i);
				if(Player->IsLocallyControlled())
				{
					UGameplayStatics::SpawnSound2D(Player, SoundPutDownPile, 1);
				}
			}
		}
	}
	else //sinon on veut prendre une pile
	{
		for (int i = 0; i < 3; ++i)
		{
			if (LookedAtMesh == ArrayHolders[i] && ArrayPiles[i])
			{
				ServerPickUp(Player, i);
				if(Player->IsLocallyControlled())
				{
					UGameplayStatics::SpawnSound2D(Player, SoundPickupPile, 1);
				}
			}
		}
	}
}

void ASGObj_EnergyStock::DrainEnergyPile_Implementation(float DeltaTime)
{
	// for (int i = 0; i < 3; ++i)
	// {
	// 	if (ArrayPiles[i])
	// 	{
	// 		if (ArrayPiles[i]->Energy > 0)
	// 		{
	// 			ArrayPiles[i]->Energy -= DrainEnergyRate * DeltaTime;
	// 			GameState->ModifyShipEnergy(DrainEnergyRate * DeltaTime);
	// 			TRACE("drain energy %f", DrainEnergyRate * DeltaTime);
	// 		}
	// 	}
	// }
}


void ASGObj_EnergyStock::ServerPutDown_Implementation(ASGPlayer_Character* Player, int index)
{
	TRACE("Server put down");
	ServerRPCPutDownPile(Player, index);
}


void ASGObj_EnergyStock::ServerPickUp_Implementation(ASGPlayer_Character* Player, int index)
{
	TRACE("Server pick up");
	MulticastPickUpPile(Player, index);

	int NumberOfPilesTaken = 0;
	//on vérifie combien de joueurs ont pris leur pile
	for (int i = 0; i < 3; ++i)
	{
		if (ArrayPiles[i] == nullptr)
			NumberOfPilesTaken ++;
	}

	TRACE("NumberOfPilesTaken %d", NumberOfPilesTaken)
	TRACE("GetNumPlayers %d", GetWorld()->GetAuthGameMode()->GetNumPlayers())

	//si il manque le même nombre de pile qu'il y a de joueur, on conclu que toutes les piles ont été prises
	if (NumberOfPilesTaken == GetWorld()->GetAuthGameMode()->GetNumPlayers())
	{
		GameState->TutorialManager->ValidateTutorialStep(TakingBattery);
	}
}

void ASGObj_EnergyStock::ServerRPCPutDownPile_Implementation(ASGPlayer_Character* Player, int index)
{
	if (Player->HoldedPile)
	{
		//j'attache la pile au holder
		Player->HoldedPile->AttachToComponent(ArraySceneComponents[index],
		                                      FAttachmentTransformRules::SnapToTargetIncludingScale);
		//je set la reference à l'index
		ArrayPiles[index] = Player->HoldedPile;
		Player->HoldedPile->SetOwnerNoSee(false);

		//je remove la ref du joueur
		Player->HoldedPile = nullptr;
		TRACE("Multicast Put down pile");

		
	}
}


void ASGObj_EnergyStock::MulticastPickUpPile_Implementation(ASGPlayer_Character* Player, int index)
{
	if(Player && Player->HoldedPile == nullptr)
	{
		//j'attache la pile au joueur
		ArrayPiles[index]->AttachToComponent(Player->PileSocket, FAttachmentTransformRules::SnapToTargetIncludingScale);
		//je set la reference dans le pawn
		Player->HoldedPile = ArrayPiles[index];
		Player->HoldedPile->SetOwner(Player);
		//je dis qu'on a plus de pile pour cet index là
		ArrayPiles[index] = nullptr;
		TRACE("Multicast Picked up pile index %d",index);
		Player->HoldedPile->SetOwnerNoSee(true);
	}
	
	
}


void ASGObj_EnergyStock::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASGPlayer_Character::StaticClass()))
	{
		ASGPlayer_Character* tmp = Cast<ASGPlayer_Character>(OtherActor);
		if (tmp)
		{
			if (tmp->IsLocallyControlled())
			{
				PlayerNear = tmp;
			}
		}

		// SetOwner(Cast<ASGPlayer_Character>(OtherActor));
		// TRACE("set owner %s",*GetOwner()->GetName())
	}
}

void ASGObj_EnergyStock::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
	{
		PlayerNear = nullptr;
	}
}
