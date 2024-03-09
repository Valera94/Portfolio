// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "GameFramework/SaveGame.h"
#include "PortfolioSaveGame.generated.h"

/**
 *
 */

class UPortfolioSaveGame;


//All inputs settings
USTRUCT(BlueprintType)
struct FInputInformation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FKey KeyIcon;
	UPROPERTY(BlueprintReadWrite)
	uint8 Index;

};

//State container view and arr all inputs
USTRUCT(BlueprintType)
struct FSetting
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FInputInformation> ArrInputs;

	UPROPERTY(BlueprintReadWrite)
	bool ActivateButtonMenuHotKey_1;
	UPROPERTY(BlueprintReadWrite)
	bool ActivateButtonMenuHotKey_2;
	UPROPERTY(BlueprintReadWrite)
	bool ActivateButtonMenuHotKey_3;
	UPROPERTY(BlueprintReadWrite)
	bool ActivateButtonMenuHotKey_4;
};

/*
 * We store the configuration data and use the
 * interface "HUDInterfaceSettings" to update the data without using Save and Load.
 * After clicking Save, we store the data.
 */

UCLASS()
class PORTFOLIO_API UPortfolioSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FSetting SettingSave;


};
