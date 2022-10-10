// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_Graviton.h"

ASGObj_Graviton::ASGObj_Graviton()
{
	BaseDownGraviton = CreateDefaultSubobject<UStaticMeshComponent>("BaseDownGraviton");
	BaseDownGraviton->SetupAttachment(RootComponent);
	BaseUpGraviton = CreateDefaultSubobject<UStaticMeshComponent>("BaseUpGraviton");
	BaseUpGraviton->SetupAttachment(BaseDownGraviton);
	SphereGraviton = CreateDefaultSubobject<UStaticMeshComponent>("SphereGraviton");
	SphereGraviton->SetupAttachment(BaseDownGraviton);
}
