// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_SD_WidgetTextDamage.h"
#include "UW_ShowDamage_Damage.h"


UAC_SD_WidgetTextDamage::UAC_SD_WidgetTextDamage()
{
}

void UAC_SD_WidgetTextDamage::CreateArrWidgets()
{
	ArrWidgetClass.Init(0, HowManyWidgetsDoNeedCreate);

	if (this->GetWidgetClass() != nullptr)
	{
		for (int a = 0; a < HowManyWidgetsDoNeedCreate; a++)
		{
			//UUW_ShowDamage_Damage* NewWidget = Cast<UUW_ShowDamage_Damage>(CreateWidget(GetWorld(), this->GetWidgetClass(), *(GetWidgetClass()->GetName().Append(FString::FromInt(a)))));
			////ArrWidgetClass.Add(NewWidget);
			//ArrWidgetClass[a] = NewWidget;

			ArrWidgetClass[a] = Cast<UUW_ShowDamage_Damage>(CreateWidget(GetWorld(), this->GetWidgetClass(), *(GetWidgetClass()->GetName().Append(FString::FromInt(a)))));

		}
	}
}

void UAC_SD_WidgetTextDamage::ShowDamageWidget_Implementation(const int SelectAttribute, const int Damage)
{
	LastSelectedWidgetFromArr == HowManyWidgetsDoNeedCreate-1 ? LastSelectedWidgetFromArr = 0 : LastSelectedWidgetFromArr++;

	if (ArrWidgetClass[LastSelectedWidgetFromArr] == nullptr || ArrWidgetClass.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, " 'UAC_SD_WidgetTextDamage' -> NoValidArr or Empty");

		return;
	}
	else
	{
		ArrWidgetClass[LastSelectedWidgetFromArr]->AddToScreen(SelectAttribute, Damage);
	}
}

void UAC_SD_WidgetTextDamage::BeginPlay()
{
	Super::BeginPlay();
	
	CreateArrWidgets();
}

