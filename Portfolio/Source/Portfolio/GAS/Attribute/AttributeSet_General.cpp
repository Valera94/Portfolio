// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet_General.h"

#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"

UAttributeSet_General::UAttributeSet_General()
{
}

UAC_PortfolioAbilitySystem* UAttributeSet_General::GetAbilitySystemComponent() const
{
	return  Cast<UAC_PortfolioAbilitySystem>(GetOwningAbilitySystemComponent());
}



