// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JeninResidentActor.generated.h"

UCLASS()
class JENIN_API AJeninResidentActor : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ResidentStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere) 
	UCapsuleComponent* CapsuleCollider;

	

	//UPROPERTY(EditAnywhere)
	//UCharacterMovementComponent* MovementComponent;
	
public:
	// Sets default values for this actor's properties
	AJeninResidentActor();

	bool IsSelected;
	UFUNCTION(Server, Reliable)
	void Server_MoveToDestination(FVector TransitDestination, float dTime);


	bool MoveResident;
	FVector MoveDestination;
	void MoveToDestination(FVector CachedDestination);
	void MoveTo(FVector loc);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
