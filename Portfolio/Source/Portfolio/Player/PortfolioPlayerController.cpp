// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioPlayerController.h"

#include "PortfolioCharacterAbility.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/AssetManager.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Portfolio/HUD/AbilityInterface.h"
#include "Portfolio/HUD/PortfolioHUD.h"

void APortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->StartCameraFade(1.f, 1.f, 0.f, FLinearColor::Black);

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);

	SetShowMouseCursor(true);
}

bool APortfolioPlayerController::InputKey(const FInputKeyParams& Params)
{
	if (OldPressKey != Params.Key.ToString() && Params.Event == EInputEvent::IE_Pressed)
	{
		OldPressKey = Params.Key.ToString(); //Write


		AsyncTask(ENamedThreads::AnyThread, [ThisWorld = GetWorld(), Params]()
			{
				TArray<UUserWidget*> AllWhoHaveInterface;
				UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(ThisWorld, AllWhoHaveInterface, UAbilityInterface::StaticClass(), false);

				for (UUserWidget*& i : AllWhoHaveInterface)
				{
					AsyncTask(ENamedThreads::GameThread, [Widget = MoveTemp(i), Params]()
						{
							Cast<IAbilityInterface>(Widget)->PressInput(Params.Key.ToString());
						});
				}

			});
	}
	else if (OldPressKey == Params.Key.ToString() && Params.Event != EInputEvent::IE_Released)
	{
		OldPressKey = ""; //Clear
	}

	return Super::InputKey(Params);
}

void APortfolioPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}
