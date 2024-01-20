// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfigData.h"


EClickStatus UInputConfigData::GetStatusInput(const EWhatWasPressed& InformationAboutClick)
{
	EClickStatus ClickStatus = InputStatusTMap[InformationAboutClick];

	return EClickStatus(ClickStatus);
}

void UInputConfigData::ChangeStatusInput(const EWhatWasPressed& InformationAboutClick, const EClickStatus& ClickStatus)
{
	InputStatusTMap[InformationAboutClick] = ClickStatus;
}
