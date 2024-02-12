// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_General_Button.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Portfolio/ConstructorChar/CharacterCreator.h"
#include "Portfolio/ConstructorChar/InterfaceCharacterCreator.h"

void UUW_General_Button::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnPressed.AddUniqueDynamic(this, &UUW_General_Button::ClickComplete);
}

void UUW_General_Button::ClickComplete()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), FoundWidgets, UInterfaceCharacterCreator::StaticClass(),false);
	for (auto i : FoundWidgets)
	{
		Cast<UUW_CharacterCreator>(i)->FClickComplete();
	}

	TArray<AActor*> L_ArrActorWithInterface;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInterfaceCharacterCreator::StaticClass(), L_ArrActorWithInterface);

	for(auto i : L_ArrActorWithInterface)
	{
		Cast<ACharacterCreator>(i)->FClickComplete();

		Button->SetVisibility(ESlateVisibility::Collapsed);
	}
}
