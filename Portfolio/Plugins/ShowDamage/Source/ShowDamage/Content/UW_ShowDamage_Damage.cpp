// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ShowDamage_Damage.h"
#include "Animation/WidgetAnimation.h"




void UUW_ShowDamage_Damage::AddToScreen(const int SelectAttribute, const int Damage)
{
	FString TextDamage = FString::FromInt(Damage);
	const FLinearColor Color = Damage > 0 ? FLinearColor::Green : FLinearColor::Red;

	FString Attribute;
	switch (SelectAttribute)
	{
	case 0:
		Attribute = "Health ";
		break;
	case 1:
		Attribute = "Mana ";
		break;
	case 2:
		Attribute = "Energy ";
		break;

	default:0;
	}



	//Position
	AddToViewport(5);
	int32 SizeX, SizeY;
	GetOwningLocalPlayer()->GetPlayerController(GetWorld())->GetViewportSize(SizeX, SizeY);
	SetPositionInViewport(FVector2D(SizeX / 2, SizeY / 2), true);


	DisplayText->SetText(FText::FromString(Attribute.Append(TextDamage))); // Result = "Energy +20" exm.
	DisplayText->SetColorAndOpacity(FSlateColor(Color));

	PlayAnimbationBP();
}
