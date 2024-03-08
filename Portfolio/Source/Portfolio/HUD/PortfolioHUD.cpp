// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioHUD.h"
#include "UW_MainGame.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"

void APortfolioHUD::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->OnPossessedPawnChanged.AddUniqueDynamic(this, &APortfolioHUD::BindDelegatePossessed);
}

void APortfolioHUD::BindDelegatePossessed(APawn* OldPawn, APawn* NewPawn)
{
	//if (Cast<APortfolioCharacterAbility>(NewPawn))
	//{
	//	MainGameWidget->AddToViewport();
	//	MainGameWidget->SetOwningPlayer(NewPawn->GetLocalViewingPlayerController());
	//	MainGameWidget->CharacterAbility = Cast<APortfolioCharacterAbility>(NewPawn);
	//}
}
