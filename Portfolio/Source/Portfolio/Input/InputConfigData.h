// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputConfigData.generated.h"





UENUM(BlueprintType, Category = "InputConfigData")
enum class EClickStatus : uint8
{
	CS_UnPressed UMETA(DisplayName = "UnPressedClick"),
	CS_Pressed UMETA(DisplayName = "PressedClick")
};

UENUM(BlueprintType, Category = "InputConfigData")
enum class EWhatWasPressed : uint8
{
	WWP_LeftClick UMETA(DisplayName = "LeftClick "),
	WWP_RightClick UMETA(DisplayName = "RightClick "),
	WWP_MiddleClick UMETA(DisplayName = "MiddleClick "),
	WWP_WASDClick UMETA(DisplayName = "WASDClick "),
	WWP_QClick UMETA(DisplayName = "QClick "),
	WWP_EClick UMETA(DisplayName = "EClick "),
	WWP_InputSpace UMETA(DisplayName = "InputSpace "),

};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeStatusClick, const EWhatWasPressed&, WhatWasPressed, const EClickStatus&, ClickStatus);


/**
 *
 * Store pointer to Input Action for native binding
 *
*/

UCLASS()
class PORTFOLIO_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:

	//"TMap" for storing data about the statuses of pressed "Ia_Input".
	UPROPERTY()
	TMap<EWhatWasPressed, EClickStatus> InputStatusTMap
	{
		{EWhatWasPressed::WWP_LeftClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_MiddleClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_RightClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_WASDClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_QClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_EClick, EClickStatus::CS_UnPressed},
		{EWhatWasPressed::WWP_InputSpace, EClickStatus::CS_UnPressed},
	};




	//Get Status input
	UFUNCTION(BlueprintCallable, Category = "UInputConfigData")
	EClickStatus GetStatusInput(const EWhatWasPressed& InformationAboutClick);

	//Change Status input
	UFUNCTION(BlueprintCallable,Category = "UInputConfigData")
	void ChangeStatusInput(const EWhatWasPressed& InformationAboutClick, const EClickStatus& ClickStatus);


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveWASD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* TurnMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMiddleMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* WheelMiddleInputMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLeftClickMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputRightClickMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputQClick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEClick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSpace;


	//Settings

	UPROPERTY()
	float MultiplyScaleLookAxis = 100.f;

	UPROPERTY()
	float MultiplyScaleMovement = 100.f;
};
