// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Portfolio/Player/PortfolioPlayerState.h"
#include "General_ProgressBar.generated.h"

/**
 *
 */

UCLASS()
class PORTFOLIO_API UGeneral_ProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UProgressBar* ProgressBarAttribute;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float MaxAttribute;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float CurrentAttribute;

	UFUNCTION(BlueprintCallable)
	void CalculateAndChangePercent();

	virtual void NativeConstruct() override;
public:
	UPROPERTY(BlueprintReadWrite,EditInstanceOnly, meta = (ExposeOnSpawn, AllowPrivateAccess))
	EAttributeInformation AttributeInformation;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Delegate")
	void OnChangedAttribute(EAttributeInformation AttributeInformationChanged, float CurrentAttributeValue, float MaxAttributeValue);

};
