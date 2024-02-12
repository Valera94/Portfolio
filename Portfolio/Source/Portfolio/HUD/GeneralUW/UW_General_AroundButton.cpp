// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_General_AroundButton.h"

#include "Engine/AssetManager.h"
#include "Engine/AssetManagerSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Portfolio/ConstructorChar/CharacterCreator.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"


void UUW_General_AroundButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddUniqueDynamic(this, &UUW_General_AroundButton::BackCallOnClick);
}

void UUW_General_AroundButton::BackCallOnClick()
{
	for (auto i : GetParent()->GetAllChildren())
	{
		UUW_General_AroundButton* General_AroundButton = Cast<UUW_General_AroundButton>(i);
		if (i == this && General_AroundButton != nullptr)
		{
			i->SetVisibility(ESlateVisibility::HitTestInvisible);
			General_AroundButton->Change(true);


			
			TArray<UUserWidget*> OutWidgets;
			UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);
			
			for (const auto& WidgetWithInterface : OutWidgets)
			{
				Cast<UUW_CharacterCreator>(WidgetWithInterface)->FClickedGeneralAroundButton(*this); //CallFunction UInterfaceCharacterCreator::FClickedGeneralAroundButton()
			}

		}
		else if (General_AroundButton != nullptr)
		{
			i->SetVisibility(ESlateVisibility::Visible);
			General_AroundButton->Change(false);
		}
	}
}

void UUW_General_AroundButton::Change_Implementation(bool bresult)
{
}