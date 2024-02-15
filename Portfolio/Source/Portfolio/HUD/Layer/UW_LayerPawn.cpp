// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_LayerPawn.h"


bool UUW_LayerPawn::ChangeHP(float Percent)
{
	ProgressBarHealth->SetPercent(Percent);
	return false;
}

bool UUW_LayerPawn::ChangeMP(float Percent)
{
	ProgressBarMP->SetPercent(Percent);
	return false;
}

bool UUW_LayerPawn::ChangeEnergy(float Percent)
{
	ProgressBarEnergy->SetPercent(Percent);
	return false;
}

bool UUW_LayerPawn::EnableWidgetsAttribute(bool bEnableMP, bool bEnableEnergy)
{
	if (!bEnableMP) { ProgressBarMP->SetVisibility(ESlateVisibility::Collapsed); }
	if (!bEnableEnergy) { ProgressBarEnergy->SetVisibility(ESlateVisibility::Collapsed); }
	return false;
}