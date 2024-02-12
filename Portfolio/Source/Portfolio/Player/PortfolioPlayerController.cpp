// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioPlayerController.h"

void APortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->StartCameraFade(1.f, 1.f, 0.f, FLinearColor::Black);
}
