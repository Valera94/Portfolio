// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainGame.h"


void UUW_MainGame::ChangeLayerPawn(UUserWidget* UserWidget)
{
	//Binding with delegate from "ChangePawnLayer".
	ChangeWidgetLayerToOther(ELayer::Layer_Pawn, UserWidget);
}

void UUW_MainGame::NativeConstruct()
{
	Super::NativeConstruct();

	if(CharacterAbility==nullptr)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	
}


void UUW_MainGame::ChangeWidgetLayerToOther(const ELayer SelectLayerChange, UUserWidget* ChangeToNewWidget)
{
	

	switch (SelectLayerChange)
	{
	case ELayer::Layer_Pawn:

		OverlayCanvas->AddChild(ChangeToNewWidget);
		break;

	case ELayer::Layer_Info:

		OverlayCanvas->ReplaceOverlayChildAt(1, ChangeToNewWidget);
		break;

	case ELayer::Layer_Menu:

		OverlayCanvas->ReplaceOverlayChildAt(2, ChangeToNewWidget);
		break;

	}

}
