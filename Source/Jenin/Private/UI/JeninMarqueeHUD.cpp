// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMarqueeHUD.h"
#include "Kismet/GameplayStatics.h"



AJeninMarqueeHUD::AJeninMarqueeHUD()
{
	StartMousePosition = {};
	CurrentMousePosition = {};
	IsDrawing = false;
}

void AJeninMarqueeHUD::DrawHUD()
{
	
	if (IsDrawing)
	{
		//UE_LOG(LogTemp, Warning, TEXT("IsDrawing = TRUE"));

		FColor c = FColor(10, 10, 200, 128);  
		UE_LOG(LogTemp, Warning, TEXT("DrawRect - Color: %s,\n Start Pos: (%f2, %f2), \nCur Pos: (%f, %f),\nWidth: %f, Height: %f"), 
			  *c.ToString(), 
			  StartMousePosition.X, StartMousePosition.Y, CurrentMousePosition.X, CurrentMousePosition.Y,
			  (CurrentMousePosition.X - StartMousePosition.X), (CurrentMousePosition.Y - StartMousePosition.Y));

		DrawRect(c,StartMousePosition.X, StartMousePosition.Y, (CurrentMousePosition.X - StartMousePosition.X), (CurrentMousePosition.Y - StartMousePosition.Y));


		bool bSuccessfullySelected = GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePosition, SelectedActors, false, false);

		if (bSuccessfullySelected)
		{
			for (int i = 0; i < SelectedActors.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Selected Actor: %s"), *SelectedActors[i]->GetName());
				
				// ... Do something with the selected actors (e.g., highlight, apply logic)
			}
		}
	}
	else
	{
		for (int i = 0; i < SelectedActors.Num(); i++)
		{
			//SelectedActors[i].selec
		}
	}
}

	

void AJeninMarqueeHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ReceiveDrawHUD(StartMousePosition.X - CurrentMousePosition.X, StartMousePosition.Y - CurrentMousePosition.Y);

	SelectedActors.Empty();

	
}

void AJeninMarqueeHUD::MarqueePressed(const FVector2D startMousePosition)
{
	StartMousePosition = startMousePosition;
	IsDrawing = true;
}

void AJeninMarqueeHUD::MarqueeHeld(const FVector2D currentMousePosition)
{
	CurrentMousePosition = currentMousePosition;
}

void AJeninMarqueeHUD::MarqueeReleased()
{
	IsDrawing = false;
	StartMousePosition = {};
}



