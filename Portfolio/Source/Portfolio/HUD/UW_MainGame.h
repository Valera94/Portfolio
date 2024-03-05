// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "UW_MainGame.generated.h"

class UCanvasPanel;

UENUM(BlueprintType)
enum ELayer
{
	Layer_Pawn, //OverlayCanvas - index 0
	Layer_Info, //OverlayCanvas - index 1
	Layer_Menu, //OverlayCanvas - index 2
};

/**
 *
 */
UCLASS()
class PORTFOLIO_API UUW_MainGame : public UUserWidget
{
	GENERATED_BODY()

public:
	

public:

	UFUNCTION(BlueprintCallable, Category = "PortfolioHUD")
	void ChangeWidgetLayerToOther(const ELayer SelectLayerChange, UUserWidget* ChangeToNewWidget);

	UFUNCTION(BlueprintCallable, Category = "PortfolioHUD")
	void ChangeLayerPawn(UUserWidget* UserWidget);

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UOverlay* OverlayCanvas;

public:

	UPROPERTY(BlueprintReadOnly,meta = (ExposeOnSpawn))
	TObjectPtr<APortfolioCharacterAbility>CharacterAbility;

public:

	//NeedConstruction Layer
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Pawn;
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Info;
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Menu;
};
