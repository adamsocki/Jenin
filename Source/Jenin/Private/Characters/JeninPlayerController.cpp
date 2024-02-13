// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerController.h"

#include "InteractiveToolManager.h"
#include "UI/JeninMarqueeHUD.h"


AJeninPlayerController::AJeninPlayerController()
{
	IsMouseTriggered = false;
	IsMouseHeld = false;
	
}


void AJeninPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetHUD())
	{
		if (IsMouseTriggered)
		{
			AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
			FVector2D MousePosition = {};
			GetMousePosition(MousePosition.X, MousePosition.Y);
			MarqueeHUD->MarqueePressed(MousePosition);
		
			IsMouseTriggered = false;
			IsMouseHeld = true;
		}

		if(IsMouseHeld)
		{
		
			AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
			FVector2D MousePosition = {};
			GetMousePosition(MousePosition.X, MousePosition.Y);
			MarqueeHUD->MarqueeHeld(MousePosition);
		
		}
	
	
		if (!IsMouseHeld)
		{
			AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
			MarqueeHUD->IsDrawing = false;
			//UE_LOG(LogTemp, Warning, TEXT("IsMousePressed = FALSE"));

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


	
