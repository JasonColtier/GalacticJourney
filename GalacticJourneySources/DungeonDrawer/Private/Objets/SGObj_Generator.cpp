// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_Generator.h"

ASGObj_Generator::ASGObj_Generator()
{
	GeneratorMesh = CreateDefaultSubobject<UStaticMeshComponent>("GeneratorMesh");
	GeneratorMeshWheel = CreateDefaultSubobject<UStaticMeshComponent>("GeneratorMeshWheel");
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");

	GeneratorMesh->SetupAttachment(RootComponent);
	WidgetComponent->SetupAttachment(RootComponent);
	GeneratorMeshWheel->SetupAttachment(RootComponent);

	
	
}

void ASGObj_Generator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!IsSabotaged)
	{
		GeneratorMeshWheel->AddLocalRotation(FRotator(SpeedRotation*DeltaSeconds,0,0));
	}
}
