// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeninUnitWidget.h"
#include "UObject/Interface.h"
#include "IUnitSelectable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIUnitSelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JENIN_API IIUnitSelectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnSelected();
	virtual  void OnDeselected();
	virtual void OnUnitSelected(UJeninUnitWidget* Widget);
	virtual  void OnUnitDeselected(UJeninUnitWidget* Widget);
	
};
