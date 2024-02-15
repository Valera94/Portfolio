// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute_Health.h"
#include "GameplayEffectExtension.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Portfolio/HUD/Layer/UW_LayerPawn.h"
#include "ShowDamage/Content/AC_SD_WidgetTextDamage.h"

UAttribute_Health::UAttribute_Health()
	:Health(100.f)
	, HealthMax(100.f)
{
}

void UAttribute_Health::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Health, Health, OldHealth);
	if (GetActorInfo()->IsLocallyControlled())
	{
		TArray<UUserWidget*> ArrUserWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), ArrUserWidget, UHUDInterface::StaticClass(), false);

		for (UUserWidget*& i : ArrUserWidget)
		{
			Cast<IHUDInterface>(i)->ChangeHP(Health.GetCurrentValue() / HealthMax.GetCurrentValue());
		}

	}

}

void UAttribute_Health::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Health, HealthMax, OldHealthMax);
}

void UAttribute_Health::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetHealthMax());
	}
}

void UAttribute_Health::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{

		if (GetDamage() > 0)
		{

			const float LocalDamageDone = GetDamage();
			SetDamage(0.f);
			SetHealth(FMath::Clamp(GetHealth() - LocalDamageDone, 0.f, GetHealthMax()));


			//Damage
			UAC_SD_WidgetTextDamage* AC_SD_WidgetTextDamage = Cast<UAC_SD_WidgetTextDamage>(GetActorInfo()->AvatarActor->GetComponentByClass(UAC_SD_WidgetTextDamage::StaticClass()));
			if (AC_SD_WidgetTextDamage != nullptr)
			{
				AC_SD_WidgetTextDamage->Client_ShowDamageWidget(-LocalDamageDone,FLinearColor::Red);
			}
		}
	}
}

void UAttribute_Health::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Health, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Health, HealthMax, COND_None, REPNOTIFY_Always);
}