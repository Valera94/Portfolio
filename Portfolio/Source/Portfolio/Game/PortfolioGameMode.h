// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortfolioGameMode.generated.h"

UCLASS(Abstract)
class APortfolioGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APortfolioGameMode();


	virtual void OnPostLogin(AController* NewPlayer) override;
};



