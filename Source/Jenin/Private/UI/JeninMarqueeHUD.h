﻿// Fill out your copyright notice in the Description page of Project Settings.

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

public:
	FVector2D StartMousePosition;
	FVector2D CurrentMousePosition;

	bool IsDrawing;


	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;
	
	void MarqueePressed(FVector2D startMousePosition);
	void MarqueeHeld(FVector2D currentMousePosition);
	void MarqueeReleased();

	TArray<AJeninResidentActor*>  SelectedActors;

	
};