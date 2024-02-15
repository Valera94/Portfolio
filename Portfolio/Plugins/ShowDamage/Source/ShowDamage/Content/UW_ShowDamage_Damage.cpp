// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ShowDamage_Damage.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"




void UUW_ShowDamage_Damage::AddToScreen(const int Damage,const FLinearColor LinearColor)
{
	AddToViewport();
	int32 SizeX, SizeY;
	GetOwningLocalPlayer()->GetPlayerController(GetWorld())->GetViewportSize(SizeX, SizeY);
	SetPositionInViewport(FVector2D(SizeX / 2, SizeY / 2), true);
	DisplayText->SetText(FText::FromString(FString::FromInt(Damage)));
	DisplayText->SetColorAndOpacity(FSlateColor(LinearColor));
	PlayAnimbationBP();
}
