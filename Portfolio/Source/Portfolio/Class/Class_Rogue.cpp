// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Rogue.h"

#include "Portfolio/GAS/Attribute/Attribute_Energy.h"

// Sets default values
AClass_Rogue::AClass_Rogue()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Energy = CreateDefaultSubobject<UAttribute_Energy>("UAttribute_Energy");

}
