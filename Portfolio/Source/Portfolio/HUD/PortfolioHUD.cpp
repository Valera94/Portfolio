// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioHUD.h"

#include "UW_MainGame.h"


void APortfolioHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(MainGameWidget)
	{
		MainGameWidget->AddToViewport(); //Create
		
	}
	
}
