// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_CharacterCreator.h"
#include "Camera/CameraLensEffectInterface.h"
#include "Portfolio/HUD/GeneralUW/UW_General_AroundButton.h"
#include "UObject/Interface.h"
#include "InterfaceCharacterCreator.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UInterfaceCharacterCreator : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PORTFOLIO_API IInterfaceCharacterCreator
{
	GENERATED_BODY()

public:
	virtual bool FChangeGender(const int32 IndexSelect) { return false; };
	virtual bool FChangeRace(const int32 IndexSelect) { return false; };
	virtual bool FChangeClass(const int32 IndexSelect) { return false; };

	// SelectedType - 0 - CLass, 1 - Gender, 2 - Race
	virtual bool FChangeText(const int32 SelectedType, const FString& TopText, const FString& InfoText) { return false; };

	virtual bool FReturnRowDataTable(const FDataTableCharacterCreator& RowDataTable) { return false; };
	virtual bool FClickedGeneralAroundButton(UUW_General_AroundButton& WhoClicked) { return true; };

	virtual bool FClickComplete() { return false; };
};