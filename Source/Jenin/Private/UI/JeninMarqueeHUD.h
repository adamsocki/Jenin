// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UI/IUnitSelectable.h"
#include "JeninUnitAreaWidget.h"
#include "Actors/JeninResidentActor.h"
#include "Core/JeninPlayerState.h"
#include "GameFramework/HUD.h"
#include "JeninMarqueeHUD.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninMarqueeHUD : public AHUD, public IIUnitSelectable
{
	GENERATED_BODY()

	
	AJeninMarqueeHUD();
	
	
	
protected:
	virtual void BeginPlay() override;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UJeninUnitAreaWidget> UnitAreaWidget;

public:
	FVector2D StartMousePosition;
	FVector2D CurrentMousePosition;


	virtual void OnUnitSelected(UJeninUnitWidget* UnitWidget) override;
	virtual void OnUnitDeselected(UJeninUnitWidget* UnitWidget) override;
	
	bool IsDrawing;

	APlayerController* PlayerController;
	AJeninPlayerState* JeninPlayerState;

	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;
	
	void MarqueeStarted(FVector2D startMousePosition);
	void MarqueeHeld(FVector2D currentMousePosition);
	void MarqueeReleased(const FVector2D releasedMousePosition);

	TArray<AActor*>  SelectedActors;
	TArray<AActor*>  ActorsInRectangle;
	//TArray<AActor*>  ActorFor;

	//UFUNCTION()
	void SwitchUIMode();

	// SELECTION MODE FUNCTIONALITY
	bool InSelectionMode;
	UPROPERTY()
	UJeninUnitAreaWidget* MyUnitAreaWidget;	
	//void AddSelectedToUnitAreaWidget(UWidget* WidgetToAdd);
	

// DEBUG CODE //
	bool DisAllowOnlySelectionOfOwnerUnits;

	
};
