// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_ScreenGraviton.h"

ASGObj_ScreenGraviton::ASGObj_ScreenGraviton()
{
	ControlPanel = CreateDefaultSubobject<UStaticMeshComponent>("ControlPanel2");
	ControlPanel->SetupAttachment(CapsuleCollider);
	ControlWidget = CreateDefaultSubobject<UWidgetComponent>("ControlWidget1");
	ControlWidget->SetupAttachment(CapsuleCollider);
}
