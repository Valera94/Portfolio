// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_ShowDamage_Damage.h"
#include "Components/WidgetComponent.h"
#include "AC_SD_WidgetTextDamage.generated.h"

/**
 *
 */

UCLASS(Config = Game)
class SHOWDAMAGE_API UAC_SD_WidgetTextDamage : public UWidgetComponent
{
	GENERATED_BODY()

public:

	
	UAC_SD_WidgetTextDamage();

	UPROPERTY(Config)
	int HowManyWidgetsDoNeedCreate = 10;

	UPROPERTY(BlueprintReadOnly)
	int LastSelectedWidgetFromArr = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<UUW_ShowDamage_Damage*> ArrWidgetClass;


	UFUNCTION(Unreliable,Client)
	void Client_CreateArrWidgets();

	UFUNCTION(Unreliable,Client,BlueprintCallable)
	void Client_ShowDamageWidget(const int Damage,const FLinearColor LinearColor);


	virtual void BeginPlay() override;

};
