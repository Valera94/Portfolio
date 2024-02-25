// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Portfolio/HUD/PortfolioHUD.h"
#include "Portfolio/HUD/Layer/UW_LayerPawn.h"
#include "ShowDamage/Content/AC_SD_WidgetTextDamage.h"
#include "AttributeSet_General.generated.h"

class UAC_PortfolioAbilitySystem;


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class PORTFOLIO_API UAttributeSet_General : public UAttributeSet
{
	GENERATED_BODY()

public:
	//UAC_PortfolioAbilitySystem* GetAbilitySystemComponent() const;




	/*
	*	SelectAttribute = 0_Health,1_Mana,2_Energy;
	*	Damage = >0_intsDamage, <0_ItsHeal;
	*	AvatarActor = WhoOwnerThisNotify
	*/
	void UWDamageNotify(const int SelectAttribute, const int Damage, const AActor* AvatarActor);


	//Save Current Percent Health To Max Health After Update Max Health
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	                                 const FGameplayAttributeData& MaxAttribute,
	                                 float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
