// Fill out your copyright notice in the Description page of Project Settings.


#include "General_ProgressBar.h"

void UGeneral_ProgressBar::CalculateAndChangePercent()
{
	ProgressBarAttribute->SetPercent(CurrentAttribute / MaxAttribute);
}

void UGeneral_ProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UGeneral_ProgressBar::OnChangedAttribute(EAttributeInformation AttributeInformationChanged, float CurrentAttributeValue, float MaxAttributeValue)
{
	if(AttributeInformationChanged == AttributeInformation)
	{
		CurrentAttribute = CurrentAttributeValue;
		MaxAttribute = MaxAttributeValue;
		CalculateAndChangePercent();
	}
}
