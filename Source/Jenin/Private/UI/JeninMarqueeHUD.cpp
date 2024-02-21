// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMarqueeHUD.h"

#include "Characters/JeninPlayerController.h"
#include "GameFramework/PlayerController.h"


#include "Components/DecalComponent.h"
#include "Core/JeninPlayerState.h"

AJeninMarqueeHUD::AJeninMarqueeHUD()
{
	StartMousePosition = {};
	CurrentMousePosition = {};
	IsDrawing = false;

	SelectedActors = {};
	ActorsInRectangle = {};
}

void AJeninMarqueeHUD::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetOwningPlayerController();
}

void AJeninMarqueeHUD::DrawHUD()
{
	Super::DrawHUD();
	if (IsDrawing)
	{
		//UE_LOG(LogTemp, Warning, TEXT("IsDrawing = TRUE"));
		FColor c = FColor(10, 10, 200, 128);
		UE_LOG(LogTemp, Warning, TEXT("HUD DRAWMouse Location: %s"), *StartMousePosition.ToString());

		UE_LOG(LogTemp, Warning, TEXT("DrawRect - Color: %s,\n Start Pos: (%f2, %f2), \nCur Pos: (%f, %f),\nWidth: %f, Height: %f"), 
			  *c.ToString(), 
			  StartMousePosition.X, StartMousePosition.Y, CurrentMousePosition.X, CurrentMousePosition.Y,
			  (CurrentMousePosition.X - StartMousePosition.X), (CurrentMousePosition.Y - StartMousePosition.Y));

		DrawRect(c,StartMousePosition.X, StartMousePosition.Y, (CurrentMousePosition.X - StartMousePosition.X), (CurrentMousePosition.Y - StartMousePosition.Y));

		const bool bSuccessfullySelected = GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePosition, ActorsInRectangle, false, false);

		if (bSuccessfullySelected)
		{
			for (int i = 0; i < ActorsInRectangle.Num(); i++)
			{
			
				
				if (ActorsInRectangle[i]->ActorHasTag(FName("Selectable")) && ActorsInRectangle[i]->IsOwnedBy(GetOwner()))
				{
					if (SelectedActors.Find(ActorsInRectangle[i]) == INDEX_NONE)
					{
						AActor * Resident = ActorsInRectangle[i];
						UDecalComponent* DecalComponent  = Resident->GetComponentByClass<UDecalComponent>();
						if (DecalComponent)
						{
							DecalComponent->SetVisibility(true);
							SelectedActors.Add(ActorsInRectangle[i]);
						}
					}
				}
			}
			
			for (int i = 0; i < SelectedActors.Num(); i++)
			{
				AActor *a = SelectedActors[i];
				if(ActorsInRectangle.Find(SelectedActors[i]) == INDEX_NONE)
				{
					AActor * Resident = SelectedActors[i];
					UDecalComponent* DecalComponent  = Resident->GetComponentByClass<UDecalComponent>();
					if (DecalComponent)
					{
						DecalComponent->SetVisibility(false);
						SelectedActors.RemoveAt(i);
					}
					//
				}
				//else
				
			}
			UE_LOG(LogTemp, Warning, TEXT("The Selected value is: %d"), SelectedActors.Num());
			UE_LOG(LogTemp, Warning, TEXT("The ActorinRec value is: %d"), ActorsInRectangle.Num());

			// if (SelectedActors.Num() > 0 )
			// {
			// 	AJeninPlayerState* ClientPlayerState = PlayerController->GetPlayerState<AJeninPlayerState>();
			// 	if (ClientPlayerState)
			// 	{
			// 		ClientPlayerState->ResidentMovementMode = true;
			// 		//for (int i )
			// 		//ClientPlayerState->SelectedUnits
			// 	}
			//
			// 	
			// }
			// else
			// {
			// 	AJeninPlayerState* ClientPlayerState = PlayerController->GetPlayerState<AJeninPlayerState>();
			// 	if (ClientPlayerState)
			// 	{
			// 		ClientPlayerState->ResidentMovementMode = false;
			// 	}
			// }
		}
	}
	else
	{
		for (int i = 0; i < SelectedActors.Num(); i++)
		{
			//SelectedActors[i].selec
		}
	}

	//if (ActorsInRectangle)
}

void AJeninMarqueeHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//ReceiveDrawHUD(StartMousePosition.X - CurrentMousePosition.X, StartMousePosition.Y - CurrentMousePosition.Y);

	ActorsInRectangle.Empty();
	//SelectedActors.Empty();
	//SelectedActors.Empty();

}

void AJeninMarqueeHUD::MarqueeStarted(const FVector2D startMousePosition)
{

	//APlayerController
	StartMousePosition = startMousePosition;
	IsDrawing = true;
	UE_LOG(LogTemp, Warning, TEXT("HUDMouse Location: %s"), *StartMousePosition.ToString());

}

void AJeninMarqueeHUD::MarqueeHeld(const FVector2D currentMousePosition)
{
	CurrentMousePosition = currentMousePosition;
	UE_LOG(LogTemp, Warning, TEXT("HeldHUD"));
	

}

void AJeninMarqueeHUD::MarqueeReleased(const FVector2D releasedMousePosition)
{
	IsDrawing = false;
	if (StartMousePosition == releasedMousePosition)
	{
		if (const AJeninPlayerController* JeninPC = Cast<AJeninPlayerController>(PlayerController))
		{
			FHitResult HitResult;
			JeninPC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult); // Adjust channel as needed 

			if (HitResult.bBlockingHit)
			{
				AActor* HitActor = HitResult.GetActor();
				// Your custom selection logic:
				if (HitActor->ActorHasTag(FName("Selectable"))) 
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("You selected something!"));
					//CurrentlySelectedActor = HitActor; 
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("MarqueeReleased"));
	}
	else
	{
		for (int i = 0; i < SelectedActors.Num(); i++)
		{
			
		}
	}

	
	
	UE_LOG(LogTemp, Warning, TEXT("The Selected Release PreEmptyvalue is: %d"), SelectedActors.Num());

	SelectedActors.Empty();
	UE_LOG(LogTemp, Warning, TEXT("The Selected Release PostEmptyvalue is: %d"), SelectedActors.Num());

}



