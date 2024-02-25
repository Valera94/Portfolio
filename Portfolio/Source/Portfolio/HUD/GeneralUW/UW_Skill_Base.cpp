// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Skill_Base.h"

void UUW_Skill_Base::ActivatePress_Implementation()
{

}

void UUW_Skill_Base::PressInput(const FString Input)
{
	if(ButtonText->GetText().EqualTo(FText::FromString(Input)))
	{
		ActivatePress();
	}
}
