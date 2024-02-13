// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"


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
	
protected:
	virtual void BeginPlay() override;

};
