// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_MotorPump.h"
#include "Camera/CameraComponent.h"
#include "Character/SGPlayer_Character.h"
#include "Functions/BP_FunctionLib.h"
#include "Components/AudioComponent.h"

ASGObj_MotorPump::ASGObj_MotorPump()
{
	MotorPump = CreateDefaultSubobject<UStaticMeshComponent>("MotorPump");
	MotorPump->SetupAttachment(RootComponent);

	ButtonTop = CreateDefaultSubobject<UStaticMeshComponent>("ButtonTop");
	ButtonTop->SetupAttachment(MotorPump);

	ButtonLeft = CreateDefaultSubobject<UStaticMeshComponent>("ButtonLeft");
	ButtonLeft->SetupAttachment(MotorPump);

	ButtonRight = CreateDefaultSubobject<UStaticMeshComponent>("ButtonRight");
	ButtonRight->SetupAttachment(MotorPump);
}

void ASGObj_MotorPump::BeginPlay()
{
	Super::BeginPlay();
	Buttons = { ButtonTop, ButtonLeft, ButtonRight };
	AudioComponent->SetSound(Pump_On);
}

// void ASGObj_MotorPump::PlayerInteraction()
// {
// 	// if (IsSabotaged && player)
// 	// {
// 	// 	FHitResult hitResult;
// 	// 	FCollisionQueryParams params;
// 	// 	params.AddIgnoredActor(player);
// 	// 	UCameraComponent* playerCam = player->GetFirstPersonCameraComponent();
// 	//
// 	// 	GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
// 	// 		(playerCam->GetComponentLocation() + playerCam->GetForwardVector() * 1000),
// 	// 		ECollisionChannel::ECC_Visibility);
// 	//
// 	// 	if (Buttons.Contains(hitResult.GetComponent()))
// 	// 	{
// 	// 		const int pos = Buttons.Find(Cast<UStaticMeshComponent>(hitResult.GetComponent()));
// 	//
// 	// 		if (buttonPress < 3 && pos != 0)
// 	// 		{
// 	// 			RunOnServerPump(pos);
// 	// 		}
// 	// 		else if (buttonPress >= 2 && pos == 0)
// 	// 		{
// 	// 			RunOnServerPump(pos);
// 	// 		}
// 	// 	}
// 	// }
// }

void ASGObj_MotorPump::Interact_Implementation(ASGPlayer_Character* Player)
{
	if (IsSabotaged && Player)
	{
		FHitResult hitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(Player);
		UCameraComponent* playerCam = Player->GetFirstPersonCameraComponent();

		GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
			(playerCam->GetComponentLocation() + playerCam->GetForwardVector() * 1000),
			ECollisionChannel::ECC_Visibility);

		if (Buttons.Contains(hitResult.GetComponent()))
		{
			const int pos = Buttons.Find(Cast<UStaticMeshComponent>(hitResult.GetComponent()));
			Player->AnimInteract2();
			if (buttonPress < 3 && pos != 0)
			{
				RunOnServerPump(pos, Player);
			}
			else if (buttonPress >= 2 && pos == 0)
			{
				RunOnServerPump(pos, Player);
			}
		}
	}
}

void ASGObj_MotorPump::ServerRPCDoAction_Implementation()
{
	Super::ServerRPCDoAction_Implementation();

	TRACE("Pump do action");

	ButtonTop->SetRelativeLocation(BasePoseTop);
	ButtonLeft->SetRelativeLocation(BasePoseLeft);
	ButtonRight->SetRelativeLocation(BasePoseRight);

	ButtonLeft->SetRenderCustomDepth(true);
	ButtonRight->SetRenderCustomDepth(true);

	AudioComponent->SetSound(Pump_Off);
	AudioComponent->Play();
}

void ASGObj_MotorPump::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsSabotaged)
	{
		if (!AudioComponent->IsPlaying())
		{
			AudioComponent->Play();
		}
	}
}

void ASGObj_MotorPump::RunOnServerPump_Implementation(int _buttonPress, ASGPlayer_Character* player)
{
	RunOnClientPump(_buttonPress, player);
}

void ASGObj_MotorPump::RunOnClientPump_Implementation(int _buttonPress, ASGPlayer_Character* player)
{
	FVector pos = Buttons[_buttonPress]->GetRelativeLocation();

	if (_buttonPress == 0)
	{
		Buttons[_buttonPress]->SetRelativeLocation(FVector{ pos.X, pos.Y, (pos.Z - 18) });

		AudioComponent->SetSound(Pump_Top_Hit);
		AudioComponent->Play();

		buttonPress = 0;
		nbPressLeft = 0;
		nbPressRight = 0;
		ButtonTop->SetRenderCustomDepth(false);

		AudioComponent->SetSound(PumpRepared);
		AudioComponent->Play();

		AudioComponent->SetSound(Pump_On);
		TArray<ASGPlayer_Character* > players = { Cast<ASGPlayer_Character>(GetOwner()) };
		RepeiredPump();
		player->HoldHammerEndOverlap2();
		Repaired(players);
	}
	else
	{
		if (_buttonPress == 1)
		{
			if (nbPressLeft < 7)
			{
				Buttons[_buttonPress]->SetRelativeLocation(FVector{ pos.X, pos.Y + 5, pos.Z - 5 });

				AudioComponent->SetSound(Pump_Hit[nbPressLeft]);
				AudioComponent->Play();

				++nbPressLeft;
				if (nbPressLeft == 7)
				{
					++buttonPress;
					Buttons[_buttonPress]->SetRenderCustomDepth(false);
					DownSmokeDesactivate(0);
				}
			}
			else
			{
				AudioComponent->SetSound(Pump_Hit_No_Interact);
				AudioComponent->Play();
			}
		}
		else if (_buttonPress == 2)
		{
			if (nbPressRight < 7)
			{
				Buttons[_buttonPress]->SetRelativeLocation(FVector{ pos.X, pos.Y - 5, pos.Z - 5 });

				AudioComponent->SetSound(Pump_Hit[nbPressRight]);
				AudioComponent->Play();

				++nbPressRight;
				if (nbPressRight == 7)
				{
					++buttonPress;
					Buttons[_buttonPress]->SetRenderCustomDepth(false);
					DownSmokeDesactivate(1);
				}
			}
			else
			{
				AudioComponent->SetSound(Pump_Hit_No_Interact);
				AudioComponent->Play();
			}
		}
		if (buttonPress == 2)
		{
			ButtonTop->SetRenderCustomDepth(true);
			UpSmokeActivate();
		}
	}
}
