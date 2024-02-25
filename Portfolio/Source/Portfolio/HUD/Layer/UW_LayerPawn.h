// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Portfolio/GAS/Data/DA_DefaultSettings.h"
#include "Portfolio/HUD/HUDInterface.h"
#include "UW_LayerPawn.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API UUW_LayerPawn : public UUserWidget, public IHUDInterface
{
	GENERATED_BODY()


	virtual void NativeConstruct() override;

	

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "ContainerUW", meta = (BindWidget))
	TObjectPtr< UVerticalBox >VerticalBoxAttribute;

	UPROPERTY(BlueprintReadOnly, Category = "Inforamtion", meta = (BindWidget))
	TObjectPtr<UProgressBar >ProgressBarHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Inforamtion", meta = (BindWidget))
	TObjectPtr<UProgressBar >ProgressBarMP;
	UPROPERTY(BlueprintReadOnly, Category = "Inforamtion", meta = (BindWidget))
	TObjectPtr<UProgressBar >ProgressBarEnergy;

	virtual void IHI_ChangeEnergyAttribute(FVector2D Value) override;
	virtual void IHI_ChangeManaAttribute(FVector2D Value) override;
	virtual void IHI_ChangeHealthAttribute(FVector2D Value) override;


};
