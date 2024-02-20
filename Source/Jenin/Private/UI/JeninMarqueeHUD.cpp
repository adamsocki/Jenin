// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninMarqueeHUD.h"

#include "Characters/JeninPlayerController.h"
#include "GameFramework/PlayerController.h"


#include "Components/DecalComponent.h"

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
				UE_LOG(LogTemp, Warning, TEXT("Selected Actor: %s"), *ActorsInRectangle[i]->GetName());
				
				ENetRole MyRole = ActorsInRectangle[i]->GetLocalRole();

				FString RoleString;
				switch(MyRole)
				{
				case ROLE_None: RoleString = "None"; break;
				case ROLE_SimulatedProxy: RoleString = "Simulated Proxy"; break;
				case ROLE_AutonomousProxy: RoleString = "Autonomous Proxy"; break;
				case ROLE_Authority: RoleString = "Authority"; break;
				}

				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Actor Role: %s"), *RoleString));
				AActor* OwnerActor = ActorsInRectangle[i]->GetOwner();
				if (OwnerActor)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, OwnerActor->GetName());
				}
				if (ActorsInRectangle[i]->ActorHasTag(FName("Selectable")) && ActorsInRectangle[i]->IsOwnedBy(GetOwner()))
				{
					AActor * Resident = ActorsInRectangle[i];
					UDecalComponent* DecalComponent  = Resident->GetComponentByClass<UDecalComponent>();

					SelectedActors.Add(ActorsInRectangle[i]);
					if (DecalComponent)
					{
						DecalComponent->SetVisibility(true); 
					}
				}
			}
			
			for (int i = 0; i < SelectedActors.Num(); i++)
			{
				if(ActorsInRectangle.Find(SelectedActors[i]) == INDEX_NONE)
				{
					AActor * Resident = SelectedActors[i];
					UDecalComponent* DecalComponent  = Resident->GetComponentByClass<UDecalComponent>();
					if (DecalComponent)
					{
						DecalComponent->SetVisibility(false); 
					}
				}
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
	//ReceiveDrawHUD(StartMousePosition.X - CurrentMousePosition.X, StartMousePosition.Y - CurrentMousePosition.Y);

	ActorsInRectangle.Empty();
	//SelectedActors.Empty();
}

void AJeninMarqueeHUD::MarqueePressed(const FVector2D startMousePosition)
{
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
}



