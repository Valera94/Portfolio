// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioGameMode.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"

APortfolioGameMode::APortfolioGameMode()
{

}

void APortfolioGameMode::OnPostLogin(AController* NewPlayer)
{
	if (Cast<APortfolioCharacterAbility>(DefaultPawnClass))
	{
		APortfolioCharacterAbility* NewChar = GetWorld()->SpawnActor<APortfolioCharacterAbility>(APortfolioCharacterAbility::StaticClass(), ChoosePlayerStart(NewPlayer)->GetActorTransform());
		NewPlayer->Possess(NewChar);
	}
}
