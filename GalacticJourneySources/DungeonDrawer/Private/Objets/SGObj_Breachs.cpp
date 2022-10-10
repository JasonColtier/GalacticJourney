// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_Breachs.h"
#include "Camera/CameraComponent.h"
#include "Character/SGPlayer_Character.h"
#include "Net/UnrealNetwork.h"
#include "DungeonDrawer/DungeonDrawer.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASGObj_Breachs::ASGObj_Breachs()
{
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>("tPlateMesh");
	PlateMesh->SetupAttachment(RootComponent);

	ScrewMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("VisMesh1");
	ScrewMesh1->SetupAttachment(PlateMesh);

	ScrewMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("VisMesh2");
	ScrewMesh2->SetupAttachment(PlateMesh);

	ScrewMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("VisMesh3");
	ScrewMesh3->SetupAttachment(PlateMesh);

	ScrewMesh4 = CreateDefaultSubobject<UStaticMeshComponent>("VisMesh4");
	ScrewMesh4->SetupAttachment(PlateMesh);

	Breach = CreateDefaultSubobject<UStaticMeshComponent>("Breach");
	Breach->SetupAttachment(PlateMesh);

	BreachParticle = CreateDefaultSubobject<UStaticMeshComponent>("BreachParticle");
	BreachParticle->SetupAttachment(RootComponent);
}

void ASGObj_Breachs::BeginPlay()
{
	Super::BeginPlay();

	Breach->SetVisibility(false);
	LMesh = { PlateMesh, ScrewMesh1, ScrewMesh2, ScrewMesh3, ScrewMesh4 };

	BreachParticle->SetVisibility(false);

	for (UStaticMeshComponent* mesh : LMesh)
	{
		mesh->SetVisibility(false);
	}
}


void ASGObj_Breachs::ServerRPCDoAction_Implementation()
{
	Super::ServerRPCDoAction_Implementation();

	Breach->SetVisibility(true);

	AudioComponent->SetSound(BreachAparition);
	AudioComponent->Play();

	BreachParticle->SetVisibility(true);

	for (UStaticMeshComponent* mesh : LMesh)
	{
		mesh->SetVisibility(false);
		mesh->SetMaterial(0, TransparenceInstance);
	}
}

void ASGObj_Breachs::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsSabotaged)
	{
		if (!AudioComponent->IsPlaying() && FirstAction)
		{
			AudioComponent->SetSound(BreachWind);
			AudioComponent->Play();
		}
	}
}

// void ASGObj_Breachs::PlayerInteraction()
// {
// 	// TRACESCREEN("AllPlayerInteraction");
// 	//
// 	// if (IsSabotaged && player)
// 	// {
// 	// 	ListeIndex = -1;
// 	//
// 	// 	//Raycast
// 	// 	FHitResult hitResult;
// 	// 	FCollisionQueryParams params;
// 	// 	params.AddIgnoredActor(player);
// 	// 	UCameraComponent* playerCam = player->GetFirstPersonCameraComponent();
// 	// 	
// 	// 	GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
// 	// 		(playerCam->GetComponentLocation() + playerCam->GetForwardVector() * 1000),
// 	// 		ECollisionChannel::ECC_Visibility);
// 	//
// 	// 	//Si c'est la premiere action du joueur sur la brèche
// 	// 	if (firstAction)
// 	// 	{
// 	// 		//Si le joueur regarde bien la plaque de la brèche
// 	// 		if (LMesh[0] == hitResult.GetComponent())
// 	// 		{
// 	// 			ListeIndex = 0;
// 	// 		}
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		//Si le joueur regarde une des vis
// 	// 		if (LMesh.Contains(hitResult.GetComponent()))
// 	// 		{
// 	// 			//Je réccupère la position de la vis dans la liste
// 	// 			ListeIndex = LMesh.Find(Cast<UStaticMeshComponent>(hitResult.GetComponent()));
// 	// 		}
// 	// 	}
// 	//
// 	// 	//Si j'ai trouver un mesh de ma liste j'appel la fonction serveur
// 	// 	if (ListeIndex != -1)
// 	// 		RunOnServerBreach(ListeIndex);
// 	//
// 	// 	//if (!LMesh.IsValidIndex(0))
// 	// 	//{
// 	// 	//	ListeIndex = -1;
// 	// 	//	RunOnServerBreach_Implementation(ListeIndex);
// 	// 	//}
// 	// }
// }

void ASGObj_Breachs::Interact_Implementation(ASGPlayer_Character* Player)
{
	TRACESCREEN("AllPlayerInteraction");

	if (IsSabotaged && Player)
	{
		ListeIndex = -1;

		//Raycast
		FHitResult hitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(Player);
		UCameraComponent* playerCam = Player->GetFirstPersonCameraComponent();

		GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
			(playerCam->GetComponentLocation() + playerCam->GetForwardVector() * DistanceToInteract),
			ECollisionChannel::ECC_Visibility);

		//Si c'est la premiere action du joueur sur la brèche
		if (FirstAction)
		{
			//Si le joueur regarde bien la plaque de la brèche
			if (LMesh[0] == hitResult.GetComponent())
			{
				ListeIndex = 0;
			}
		}
		else
		{
			//Si le joueur regarde une des vis
			if (LMesh.Contains(hitResult.GetComponent()))
			{
				//Je réccupère la position de la vis dans la liste
				ListeIndex = LMesh.Find(Cast<UStaticMeshComponent>(hitResult.GetComponent()));
			}
		}

		//Si j'ai trouver un mesh de ma liste j'appel la fonction serveur
		if (ListeIndex != -1)
			RunOnServerBreach(ListeIndex, Player);

		Player->AnimInteract2();

		//if (!LMesh.IsValidIndex(0))
		//{
		//	ListeIndex = -1;
		//	RunOnServerBreach_Implementation(ListeIndex);
		//}
	}
}

void ASGObj_Breachs::RunOnServerBreach_Implementation(int _listeIndex, ASGPlayer_Character* player)
{
	RunOnClientBreah(_listeIndex, player);
}

void ASGObj_Breachs::RunOnClientBreah_Implementation(int _listeIndex, ASGPlayer_Character* player)
{
	if (_listeIndex != -1)
	{
		UStaticMeshComponent* tmp = LMesh[_listeIndex];
		//Je set le material de mon mesh et le retire de la liste
		LMesh[_listeIndex]->SetMaterial(0, MetalInstance);
		LMesh.RemoveAt(_listeIndex);

		//Si c'est ma première action je rend visible les vis avec le bon material
		if (FirstAction)
		{
			AudioComponent->SetSound(BreachPlate);
			AudioComponent->Play();
			Breach->SetVisibility(false);
			BreachParticle->SetVisibility(false);

			for (UStaticMeshComponent* mesh : LMesh)
			{
				mesh->SetMaterial(0, TransparenceInstance);
				mesh->SetVisibility(true);
			}
			FirstAction = false;
		}
		else
		{
			ScrewMovement(tmp);
			AudioComponent->SetSound(BreachScrew);
			AudioComponent->Play();
		}

		if (!LMesh.IsValidIndex(0))
		{
			FirstAction = true;
			LMesh = { PlateMesh, ScrewMesh1, ScrewMesh2, ScrewMesh3, ScrewMesh4 };
			TArray<ASGPlayer_Character* > players = { Cast<ASGPlayer_Character>(GetOwner()) };
			player->HoldScrewdriverEndOverlap2();
			Repaired(players);
		}
	}
}

void ASGObj_Breachs::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	//TRACESCREEN("PlayerOnOverlap");
	

	if (IsSabotaged)
	{
		
		if (FirstAction)
		{
			LMesh[0]->SetMaterial(0, TransparenceInstance);
			LMesh[0]->SetVisibility(true);
		}
		else
		{
			for (UStaticMeshComponent* mesh : LMesh)
			{
				mesh->SetVisibility(true);
			}
		}
	}
}

void ASGObj_Breachs::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	//TRACESCREEN("PlayerEndOverlap");

	if (IsSabotaged)
	{
		for (UStaticMeshComponent* mesh : LMesh)
		{
			mesh->SetVisibility(false);
		}
	}
}


//void ASGObj_Breachs::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME(ASGObj_Breachs, tmp_Mesh);
//	DOREPLIFETIME(ASGObj_Breachs, ListeIndex);
//	//DOREPLIFETIME(ASGObj_Breachs, actionIndex);
//}
