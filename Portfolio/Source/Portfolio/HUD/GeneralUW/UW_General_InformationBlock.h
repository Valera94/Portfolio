// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "UW_General_InformationBlock.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UUW_General_InformationBlock : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TopText;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UMultiLineEditableTextBox* InfoBlock;

	// 0 - CLass, 1 - Gender, 2 - Race
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 IndexTag;
};
