﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "JeninCharacter.generated.h"

UCLASS()
class JENIN_API AJeninCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJeninCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseLeftClickAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RotateAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SpawnAction = nullptr;

	void MoveTriggered(const FInputActionValue& Value);	
	void RotateTriggered(const FInputActionValue& Value);
	void ZoomTriggered(const FInputActionValue& Value);
	
	void MouseLeftClickTriggered(const FInputActionValue& Value);
	void MouseLeftClickOngoing(const FInputActionValue& Value);
	void MouseLeftClickCompleted(const FInputActionValue& Value);

	void SpawnTriggered(const FInputActionValue& Value);
	void SpawnCompleted(const FInputActionValue& Value);

	
	UFUNCTION(Server, Unreliable)
	void Server_MoveForward(float ForwardMovementFloat);

	UFUNCTION(Server, Reliable)
	void SpawnResident();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopSpawn();
	
	int32 Character_MapID;

	bool IsSpawning;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;
	bool IsFiringWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resident")
	TSubclassOf<AActor> ResidentBPClass;

	

	/** A timer handle used for providing the fire rate delay in-between spawns.*/
	FTimerHandle FiringTimer;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
