// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/JeninResidentActor.h"
#include "GameFramework/HUD.h"
#include "JeninMarqueeHUD.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninMarqueeHUD : public AHUD
{
	GENERATED_BODY()

	AJeninMarqueeHUD();

	
protected:
	virtual void BeginPlay() override;

public:
	FVector2D StartMousePosition;
	FVector2D CurrentMousePosition;

	bool IsDrawing;

	APlayerController* PlayerController;

	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;
	
	void MarqueeStarted(FVector2D startMousePosition);
	void MarqueeHeld(FVector2D currentMousePosition);
	void MarqueeReleased(const FVector2D releasedMousePosition);

	TArray<AActor*>  SelectedActors;
	TArray<AActor*>  ActorsInRectangle;

// DEBUG CODE //
	bool DisAllowOnlySelectionOfOwnerUnits;


	
};
