// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
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

	UAttributeSet_General();
	UAC_PortfolioAbilitySystem* GetAbilitySystemComponent() const;




};
