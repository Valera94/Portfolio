// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioHUD.h"
#include "UW_MainGame.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include <Kismet\GameplayStatics.h>

void APortfolioHUD::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->OnPossessedPawnChanged.AddUniqueDynamic(this, &APortfolioHUD::BindDelegatePossessed);

	//if(MenuWidget)
	//{
	//	
	//}
}

void APortfolioHUD::BindDelegatePossessed_Implementation(APawn* OldPawn, APawn* NewPawn)
{
}

void APortfolioHUD::SaveSettingKeyboard(FSetting Setting)
{
	UPortfolioSaveGame* SaveGameConfig = Cast<UPortfolioSaveGame>(UGameplayStatics::CreateSaveGameObject(UPortfolioSaveGame::StaticClass()));
	SaveGameConfig->SettingSave = Setting;
	UGameplayStatics::SaveGameToSlot(Cast<USaveGame>(SaveGameConfig), "SaveSettings", 0);
}

FSetting APortfolioHUD::LoadSaveSettingKeyboard()
{
	return Cast<UPortfolioSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSettings", 0))->SettingSave;
}
