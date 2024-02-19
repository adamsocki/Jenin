// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeninBuilding.generated.h"

UCLASS()
class JENIN_API AJeninBuilding : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jenin|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingStaticMesh = nullptr;


public:
	// Sets default values for this actor's properties
	AJeninBuilding();

	
	bool IsSelected;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	float BuildingHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	bool InPlacementMode;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
