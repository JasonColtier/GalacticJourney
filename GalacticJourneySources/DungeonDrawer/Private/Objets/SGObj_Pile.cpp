// Fill out your copyright notice in the Description page of Project Settings.

#include "Objets/SGObj_Pile.h"

#include "Functions/BP_FunctionLib.h"
#include "Kismet/KismetMathLibrary.h"
#include "Objets/SGObj_EnergyStock.h"

ASGObj_Pile::ASGObj_Pile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	BottomPivotScene = CreateDefaultSubobject<USceneComponent>("BottomPivotScene");
	CylinderEnergy = CreateDefaultSubobject<UStaticMeshComponent>("CylinderEnergy");
	AudioSource = CreateDefaultSubobject<UAudioComponent>("AudioSource");

	Mesh->SetupAttachment(SceneRootComponent);
	BottomPivotScene->SetupAttachment(SceneRootComponent);
	CylinderEnergy->SetupAttachment(BottomPivotScene);
	AudioSource->SetupAttachment(SceneRootComponent);
}

void ASGObj_Pile::BeginPlay()
{
	Energy = 0;
	// ChangeEnergy(0);
	BottomPivotScene->SetRelativeScale3D(FVector(BottomPivotScene->GetComponentScale().X,
	                                             BottomPivotScene->GetComponentScale().Y, 0));
}

// Called every frame
void ASGObj_Pile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASGObj_Pile::SetOwnerNoSee(bool noSee)
{
	Mesh->SetOwnerNoSee(noSee);
	CylinderEnergy->SetOwnerNoSee(noSee);
}

void ASGObj_Pile::MulticastChangeEnergy_Implementation(float change)
{
	Energy += change;

	if (Energy > MaxEnergy)
		Energy = MaxEnergy;

	if (Energy < 0)
		Energy = 0;

	float ZSize = UKismetMathLibrary::MapRangeClamped(Energy, 0, MaxEnergy, 0, 0.4f);
	BottomPivotScene->SetRelativeScale3D(FVector(1, 1, ZSize));

	// TRACE("change %f",change);

	//si on est juste updaté par le energy stock
	if (change == 0)
	{
		//si on se vide de l'énergie
		AudioSource->Sound = BatteryOnFloating;
		if (!AudioSource->IsPlaying())
			AudioSource->Play();

		if (Energy == 0)
		{
			AudioSource->Sound = BatteryEnergyEmpty;
			AudioSource->Play();
		}
	}
}

void ASGObj_Pile::ChangeEnergy_Implementation(float change)
{
	MulticastChangeEnergy(change);
}

void ASGObj_Pile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGObj_Pile, Energy);
	DOREPLIFETIME(ASGObj_Pile, MaxEnergy);
}

// void ASGObj_Pile::ChangeEnergy(float change)
// {
// 	
// }
