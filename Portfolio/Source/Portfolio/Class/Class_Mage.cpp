// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Mage.h"

#include "Portfolio/GAS/Attribute/Attribute_Mana.h"

// Sets default values
AClass_Mage::AClass_Mage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mana = CreateDefaultSubobject<UAttribute_Mana>("UAttribute_Mana");

}

void AClass_Mage::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

