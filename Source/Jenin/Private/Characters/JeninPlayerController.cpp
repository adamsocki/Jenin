// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerController.h"



#include "InteractiveToolManager.h"
#include "JeninCharacter.h"
#include "Core/JeninPlayerState.h"
#include "UI/JeninMarqueeHUD.h"


AJeninPlayerController::AJeninPlayerController()
{
	IsMouseTriggered = false;
	IsMouseHeld = false;
	
}


void AJeninPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AJeninPlayerState* CurrentPlayerState = GetPlayerState<AJeninPlayerState>();
	AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
	//GetPlayerState

	
	if (CurrentPlayerState && MarqueeHUD)
	{
		if (CurrentPlayerState->InPlay)
		{
			if (IsMouseTriggered)
			{
				FVector2D MousePosition = {};
				GetMousePosition(MousePosition.X, MousePosition.Y);
				MarqueeHUD->MarqueePressed(MousePosition);
		
				IsMouseTriggered = false;
				IsMouseHeld = true;
			}

			if(IsMouseHeld)
			{
				FVector2D MousePosition = {};
				GetMousePosition(MousePosition.X, MousePosition.Y);
				MarqueeHUD->MarqueeHeld(MousePosition);
			}
			if (!IsMouseHeld)
			{
				MarqueeHUD->IsDrawing = false;
				//UE_LOG(LogTemp, Warning, TEXT("IsMousePressed = FALSE"));
			}

			if (IsMouseReleased)
			{
				IsMouseTriggered = false;
				IsMouseHeld = false;
				IsMouseReleased = false;
				FVector2D MousePosition = {};
				GetMousePosition(MousePosition.X, MousePosition.Y);
				MarqueeHUD->MarqueeReleased(MousePosition);


			}
		}
		
	}
	
}

void AJeninPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true; // Allows clicks 
	this->bEnableMouseOverEvents = true; // Allows mouse-over events
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	this->SetInputMode(InputMode);
}


	
