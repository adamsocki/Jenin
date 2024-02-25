// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JeninUnitAreaWidget.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API UJeninUnitAreaWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UHorizontalBox* HorizontalBoxWidget; 
};
