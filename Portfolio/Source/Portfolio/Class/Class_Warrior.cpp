// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Warrior.h"

#include "Portfolio/GAS/Attribute/AttributeSet_Rage.h"

// Sets default values
AClass_Warrior::AClass_Warrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rage = CreateDefaultSubobject<UAttributeSet_Rage>("UAttributeSet_Rage");

}
