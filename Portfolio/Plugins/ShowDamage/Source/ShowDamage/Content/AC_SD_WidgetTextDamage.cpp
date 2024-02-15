// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_SD_WidgetTextDamage.h"
#include "UW_ShowDamage_Damage.h"


UAC_SD_WidgetTextDamage::UAC_SD_WidgetTextDamage()
{
}

void UAC_SD_WidgetTextDamage::Client_CreateArrWidgets_Implementation()
{

	if (GetWidgetClass() != nullptr)
	{
		for (int a = 0; a < 50; a++)
		{
			UUW_ShowDamage_Damage* NewWidget = Cast<UUW_ShowDamage_Damage>(CreateWidget(GetWorld(), GetWidgetClass(), *(GetWidgetClass()->GetName().Append(FString::FromInt(a)))));
			ArrWidgetClass.Add(NewWidget);
		}
	}
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "need use parent widget 'UUW_ShowDamage_Damage' ");
	}
}

void UAC_SD_WidgetTextDamage::Client_ShowDamageWidget_Implementation(const int Damage,const FLinearColor LinearColor)
{
	if (ArrWidgetClass.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Empty arr");

		return;
	}

	LastSelectedWidgetFromArr == HowManyWidgetsDoNeedCreate ? LastSelectedWidgetFromArr = 0 : LastSelectedWidgetFromArr++;

	if (ArrWidgetClass[LastSelectedWidgetFromArr] == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "NoValidArr");

		return;
	}

	ArrWidgetClass[LastSelectedWidgetFromArr]->AddToScreen(Damage,LinearColor);

}

void UAC_SD_WidgetTextDamage::BeginPlay()
{
	Super::BeginPlay();
	
	Client_CreateArrWidgets();
}

