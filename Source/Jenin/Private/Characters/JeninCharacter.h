// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"

#include "Core/JeninGameState.h"
#include "Camera/CameraComponent.h"
#include "Core/JeninPlayerState.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "JeninCharacter.generated.h"

UCLASS()
class JENIN_API AJeninCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	AJeninGameState* JeninGameState ;
	AJeninPlayerState* JeninPlayerState ;


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
	TObjectPtr<UInputAction> SpawnAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resident")
	TSubclassOf<APawn> ResidentBPClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resident")
	TSubclassOf<APawn> BuildingBPClass;
	
	void MoveTriggered(const FInputActionValue& Value);	

	void SpawnTriggered(const FInputActionValue& Value);
	void SpawnCompleted(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void SpawnResident(FVector SpawnLocation);
	
	UFUNCTION(Server, Reliable)
	void SpawnBuilding(int32 ResidentSpawnCount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopSpawn();
	
	int32 Character_MapID;

	bool IsSpawning;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;
	bool IsFiringWeapon = false;
	
	float DragTolerance = 10.0f;
	bool IsMarqueeSelecting;

	/** A timer handle used for providing the fire rate delay in-between spawns.*/
	FTimerHandle FiringTimer;

protected:
	virtual void BeginPlay() override;
	

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayerInit(FVector PlayerSpawnLocation);

};
