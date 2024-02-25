// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet_General.h"

#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"
#include "Portfolio/HUD/UW_MainGame.h"


//
//UAC_PortfolioAbilitySystem* UAttributeSet_General::GetAbilitySystemComponent() const
//{
//	return  Cast<UAC_PortfolioAbilitySystem>(GetOwningAbilitySystemComponent());
//}

void UAttributeSet_General::UWDamageNotify(const int SelectAttribute, const int Damage, const AActor* AvatarActor)
{
	Cast<UAC_SD_WidgetTextDamage>(AvatarActor->GetComponentByClass(UAC_SD_WidgetTextDamage::StaticClass()))->ShowDamageWidget(SelectAttribute, Damage);
}


void UAttributeSet_General::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}