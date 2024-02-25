// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayEffect.h"

FEffectKeyPair::FEffectKeyPair()
{
}

FEffectKeyPair::FEffectKeyPair(FName id, FActiveGameplayEffectHandle Handle)
{
	Id = id;
	EffectHandle = Handle;
}
