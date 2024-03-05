// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_LayerPawn.h"

#include "Portfolio/GAS/Attribute/Attribute_Energy.h"
#include "Portfolio/HUD/UW_MainGame.h"


void UUW_LayerPawn::NativeConstruct()
{
	Super::NativeConstruct();
	ProgressBarHealth->SetPercent(1);
	ChangeProgressBarInformationAndLogic();
}

void UUW_LayerPawn::ChangeProgressBarInformationAndLogic()
{
	if (GetOwningPlayerPawn()->StaticClass() == APortfolioCharacterAbility::StaticClass())
	{

		if (Cast<APortfolioCharacterAbility>(GetOwningPlayerPawn())->GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Rage")) > 0)
		{
			ProgressBarSecond->SetPercent(0);
			ProgressBarSecond->SetFillColorAndOpacity(FLinearColor(1.f, 0.12f, 0.58f, 1.f));
		}

		if (Cast<APortfolioCharacterAbility>(GetOwningPlayerPawn())->GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Mana")) > 0)
		{
			ProgressBarSecond->SetPercent(1);
			ProgressBarSecond->SetFillColorAndOpacity(FLinearColor::Blue);
		}

		if (Cast<APortfolioCharacterAbility>(GetOwningPlayerPawn())->GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Energy")) > 0)
		{
			ProgressBarSecond->SetPercent(1);
			ProgressBarSecond->SetFillColorAndOpacity(FLinearColor::Green);
		}
	}
	//
	//if(GASComponent->TagContainer.HasTag(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Rage")))
	//{
	//	ProgressBarSecond->SetPercent(0);
	//	ProgressBarSecond->SetFillColorAndOpacity(FLinearColor(1.f, 0.12f, 0.58f, 1.f));
	//}
	//
	//if (GASComponent->TagContainer.HasTag(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Mana")))
	//{
	//	ProgressBarSecond->SetPercent(1);
	//	ProgressBarSecond->SetFillColorAndOpacity(FLinearColor::Blue);
	//}
	//
	//if (GASComponent->TagContainer.HasTag(FGameplayTag::RequestGameplayTag("Ability.CharacterConstructor.Attribute.Energy")))
	//{
	//	ProgressBarSecond->SetPercent(1);
	//	ProgressBarSecond->SetFillColorAndOpacity(FLinearColor::Green);
	//}
}

void UUW_LayerPawn::IHI_ChangeMainAttribute(FVector2D Value)
{
	ProgressBarHealth->SetPercent(Value.Y / Value.X);
}

void UUW_LayerPawn::IHI_ChangeSecondAttribute(FVector2D Value)
{
	ProgressBarSecond->SetPercent(Value.Y / Value.X);
}
