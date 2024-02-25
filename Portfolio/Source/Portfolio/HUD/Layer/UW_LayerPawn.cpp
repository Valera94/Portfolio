// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_LayerPawn.h"

#include "Portfolio/GAS/Attribute/Attribute_Energy.h"
#include "Portfolio/HUD/UW_MainGame.h"


void UUW_LayerPawn::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBarHealth->SetPercent(1);
	ProgressBarMP->SetPercent(1);
	ProgressBarEnergy->SetPercent(1);
}


void UUW_LayerPawn::IHI_ChangeEnergyAttribute(FVector2D Value)
{
	ProgressBarEnergy->SetPercent(Value.Y / Value.X);
}

void UUW_LayerPawn::IHI_ChangeManaAttribute(FVector2D Value)
{
	ProgressBarMP->SetPercent(Value.Y / Value.X);
}

void UUW_LayerPawn::IHI_ChangeHealthAttribute(FVector2D Value)
{
	ProgressBarHealth->SetPercent(Value.Y / Value.X);
}
