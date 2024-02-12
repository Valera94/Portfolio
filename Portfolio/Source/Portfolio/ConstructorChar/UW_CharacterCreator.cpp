// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_CharacterCreator.h"

#include "CharacterCreator.h"
#include "Components/Spacer.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Portfolio/HUD/GeneralUW/UW_General_AroundButton.h"

void UUW_CharacterCreator::AddToVerticalBox_Race(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance, UDataTable* DataTable)
{
	for (auto i : DataTable->GetRowNames())
	{
		//CreateDynamicMaterial
		UMaterialInstanceDynamic* MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SetMaterialInstance.LoadSynchronous());

		FDataTableCharacterCreator* L_DataTableCharacterCreator = DataTable->FindRow<FDataTableCharacterCreator>(i, nullptr);

		//CreateWidget
		UUW_General_AroundButton* Widget = Cast<UUW_General_AroundButton>(CreateWidget(GetWorld(), AroundButton));

		MaterialInstanceDynamic->SetScalarParameterValue("U_Horizontal_Select", L_DataTableCharacterCreator->struct_Race.ParameterMaterial.X);
		MaterialInstanceDynamic->SetScalarParameterValue("V_Vertical_Select", L_DataTableCharacterCreator->struct_Race.ParameterMaterial.Y);

		Widget->Image_Button->SetBrushFromSoftMaterial(MaterialInstanceDynamic);

		VerticalBox_Race->AddChild(Widget);

	}
}

void UUW_CharacterCreator::AddToHorizontalBox_Gender(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance)
{
	//CreateDynamicMaterial
	UMaterialInstanceDynamic* MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SetMaterialInstance.LoadSynchronous());

	//CreateWidget
	UUW_General_AroundButton* Widget = Cast<UUW_General_AroundButton>(CreateWidget(GetWorld(), AroundButton));
	MaterialInstanceDynamic->SetScalarParameterValue("U_Horizontal_Select", 2.f);
	Widget->Image_Button->SetBrushFromSoftMaterial(MaterialInstanceDynamic);
	HorizontalBox_Gender->AddChild(Widget);

	//CreateDynamicMaterial
	MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SetMaterialInstance.LoadSynchronous());

	//CreateWidget
	Widget = Cast<UUW_General_AroundButton>(CreateWidget(GetWorld(), AroundButton));
	MaterialInstanceDynamic->SetScalarParameterValue("U_Horizontal_Select", 1.f);
	Widget->Image_Button->SetBrushFromSoftMaterial(MaterialInstanceDynamic);
	HorizontalBox_Gender->AddChild(Widget);
}

void UUW_CharacterCreator::AddToHorizontalBox_Class(TSoftObjectPtr<UMaterialInstance> SetMaterialInstance, FDataTableCharacterCreator* RowDataTable)
{
	for (auto i : RowDataTable->struct_Class)
	{
		//CreateDynamicMaterial
		UMaterialInstanceDynamic* MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SetMaterialInstance.LoadSynchronous());

		//CreateWidget
		UUW_General_AroundButton* Widget = Cast<UUW_General_AroundButton>(CreateWidget(GetWorld(), AroundButton));

		MaterialInstanceDynamic->SetScalarParameterValue("U_Horizontal_Select", i.ParameterMaterial.X);
		MaterialInstanceDynamic->SetScalarParameterValue("V_Vertical_Select", i.ParameterMaterial.Y);

		Widget->Image_Button->SetBrushFromSoftMaterial(MaterialInstanceDynamic);
		HorizontalBox_Class->AddChild(Widget);
	}
}

void UUW_CharacterCreator::SimpleClicked()
{
	Cast<UUW_General_AroundButton>(HorizontalBox_Gender->GetAllChildren()[0])->BackCallOnClick();
	Cast<UUW_General_AroundButton>(HorizontalBox_Class->GetAllChildren()[0])->BackCallOnClick();
	Cast<UUW_General_AroundButton>(VerticalBox_Race->GetAllChildren()[0])->BackCallOnClick();
}


bool UUW_CharacterCreator::FReturnRowDataTable(const FDataTableCharacterCreator& RowDataTable)
{
	//SetBrush
	BackgroundCastleRaceImage->SetBrushFromSoftTexture(RowDataTable.BackgroundCastleRaceImage);

	return true;
}

bool UUW_CharacterCreator::FClickedGeneralAroundButton(UUW_General_AroundButton& WhoClicked)
{
	if (WhoClicked.GetParent() == HorizontalBox_Gender)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInterfaceCharacterCreator::StaticClass(), OutActors);

		for (const auto& ActorWithInterface : OutActors)
		{
			Cast<ACharacterCreator>(ActorWithInterface)->FChangeGender(
				HorizontalBox_Gender->GetAllChildren().Find(&WhoClicked));
		}
	}
	else if (WhoClicked.GetParent() == HorizontalBox_Class)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInterfaceCharacterCreator::StaticClass(), OutActors);

		for (const auto& ActorWithInterface : OutActors)
		{
			Cast<ACharacterCreator>(ActorWithInterface)->FChangeClass(
				HorizontalBox_Class->GetAllChildren().Find(&WhoClicked));
		}
	}
	else if (WhoClicked.GetParent() == VerticalBox_Race)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInterfaceCharacterCreator::StaticClass(), OutActors);

		for (const auto& ActorWithInterface : OutActors)
		{
			Cast<ACharacterCreator>(ActorWithInterface)->FChangeRace(
				VerticalBox_Race->GetAllChildren().Find(&WhoClicked));
		}
	}

	return false;
}

bool UUW_CharacterCreator::FChangeText(const int32 SelectedType, const FString& TopText, const FString& InfoText)
{

	// 0 - CLass, 1 - Gender, 2 - Race

	if(SelectedType==0)
	{
		UWG_Info_Class->TopText->SetText(FText::FromString(TopText));
		UWG_Info_Class->InfoBlock->SetText(FText::FromString(InfoText));
	}
	else if(SelectedType == 1)
	{
		UWG_Info_Gender->TopText->SetText(FText::FromString(TopText));
		UWG_Info_Gender->InfoBlock->SetText(FText::FromString(InfoText));
	}
	else if (SelectedType == 2)
	{
		UWG_Info_Race->TopText->SetText(FText::FromString(TopText));
		UWG_Info_Race->InfoBlock->SetText(FText::FromString(InfoText));
	}

	return false;
}

bool UUW_CharacterCreator::FClickComplete()
{
	RemoveFromParent();
	return false;
}
