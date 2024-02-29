// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
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

};
