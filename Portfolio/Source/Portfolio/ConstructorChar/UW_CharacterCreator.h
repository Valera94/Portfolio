// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceCharacterCreator.h"

#include "Blueprint/UserWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"

#include "Components/VerticalBox.h"
#include "Portfolio/HUD/GeneralUW/UW_General_InformationBlock.h"

#include "UW_CharacterCreator.generated.h"


/**
 *
 */

class UUW_General_AroundButton;
UCLASS(Abstract)
class PORTFOLIO_API UUW_CharacterCreator : public UUserWidget, public IInterfaceCharacterCreator
{
	GENERATED_BODY()

public:


	//----------------------
	//Containers
	//----------------------

	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Gender;

	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Class;

	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UVerticalBox* VerticalBox_Race;


	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UUW_General_InformationBlock* UWG_Info_Gender;

	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UUW_General_InformationBlock* UWG_Info_Race;

	UPROPERTY(BlueprintReadWrite, Category = "Container", meta = (BindWidget))
	UUW_General_InformationBlock* UWG_Info_Class;

	//----------------------
	//Art
	//----------------------

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Art", meta = (BindWidget))
	UImage* BackgroundCastleRaceImage;

	//----------------------
	//Need reference
	//----------------------

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UUW_General_AroundButton> AroundButton;

	UPROPERTY()
	TObjectPtr<class ACharacterCreator> CharacterCreator;

	void AddToVerticalBox_Race(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance, UDataTable* DataTable);
	void AddToHorizontalBox_Gender(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance);
	void AddToHorizontalBox_Class(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance, FDataTableCharacterCreator* RowDataTable);

	void SimpleClicked();

public:

	//Interface IInterfaceCharacterCreator
	virtual bool FReturnRowDataTable(const FDataTableCharacterCreator& RowDataTable) override;
	virtual bool FClickedGeneralAroundButton(UUW_General_AroundButton& WhoClicked) override;
	virtual bool FChangeText(const int32 SelectedType, const FString& TopText, const FString& InfoText) override;
	virtual bool FClickComplete() override;
};
