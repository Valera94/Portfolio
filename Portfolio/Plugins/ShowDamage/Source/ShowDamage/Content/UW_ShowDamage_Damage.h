// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UW_ShowDamage_Damage.generated.h"

/**
 *
 */
UCLASS(Abstract)
class SHOWDAMAGE_API UUW_ShowDamage_Damage : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> DisplayText;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnimbationBP();

	UFUNCTION()
	void AddToScreen(const int Damage, const FLinearColor LinearColor);

};
