// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "UW_General_AroundButton.generated.h"



/**
 * 
 */

enum ERaceType : uint8;
UCLASS()
class PORTFOLIO_API UUW_General_AroundButton : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:


	UPROPERTY(BlueprintReadWrite, Instanced, meta = (BindWidget))
	USizeBox* SizeBox_Button;

	UPROPERTY(BlueprintReadWrite, Instanced, meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite, Instanced, meta = (BindWidget))
	UImage* Image_Button;

	UFUNCTION()
	void BackCallOnClick();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Change(bool bresult);

	
};