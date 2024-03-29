﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Core/JeninPlayerState.h"


#include "JeninPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class JENIN_API AJeninPlayerController : public APlayerController
{
	GENERATED_BODY()

	AJeninPlayerController();

public:
	virtual void Tick(float DeltaSeconds) override;
	
	bool IsMouseTriggered;
	bool IsMouseHeld;
	bool IsMouseReleased;

	AJeninPlayerState* JeninPlayerState;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RotateAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SpawnAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SetResidentDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseLeftClickAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraMoveAction = nullptr;
	
private:
	FVector CachedDestination;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void OnSpawnStarted();

	void OnMouseLeftClickStarted(const FInputActionValue& Value);
	void OnMouseLeftClickTriggered(const FInputActionValue& Value);
	void OnMouseLeftClickCompleted(const FInputActionValue& Value);
	
	void OnSetResidentDestinationStarted(const FInputActionValue& Value);

	void OnCameraMoveTriggered(const FInputActionValue& Value);	
	void OnZoomTriggered(const FInputActionValue& Value);
	void OnRotateTriggered(const FInputActionValue& Value);
	

};
