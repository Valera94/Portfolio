// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameTeam.h"

#include "AbilitySystemComponent.h"
#include "AI_PortfolioChar.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "Engine/StaticMeshSocket.h"

DEFINE_LOG_CATEGORY(LogMiniGameTeam)

// Sets default values
AMiniGameTeam::AMiniGameTeam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	TeamAObjectComponent = CreateDefaultSubobject<UBoxComponent>("TeamAObjectComponent");
	TeamAObjectComponent->SetHiddenInGame(false);
	TeamAObjectComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TeamAObjectComponent->SetupAttachment(GetRootComponent());

	TextRenderTeamA = CreateDefaultSubobject<UTextRenderComponent>("TextRenderTeamA");
	TextRenderTeamA->SetupAttachment(TeamAObjectComponent);

	TeamBObjectComponent = CreateDefaultSubobject<UBoxComponent>("TeamBObjectComponent");
	TeamBObjectComponent->SetHiddenInGame(false);
	TeamBObjectComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TeamBObjectComponent->SetupAttachment(GetRootComponent());

	TextRenderTeamB = CreateDefaultSubobject<UTextRenderComponent>("TextRenderTeamB");
	TextRenderTeamB->SetupAttachment(TeamBObjectComponent);


	//CanBeAttachedToOtherObject;
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AMiniGameTeam::ConstructorTeam(const int Command, const  int TypeClass)
{
	if (!PortfolioChar)
	{
		UE_LOG(LogMiniGameTeam, Error, TEXT("SelectCharToSpawn is NULL !"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "SelectCharToSpawn is Null!");
		return;
	}//ExitIfNoValid

	//Location When need spawn CharacterAI
	FVector StartLocation;

	/*
	 * Create Gameplay Tag Container
	 */

	FGameplayTagContainer GameplayTagContainer;
	FGameplayTag GameplayTagTeam;
	FGameplayTag GameplayTagClass;

	// int Command   : command A = 0 ; command B = 1;
	if (Command == 0)
	{
		GameplayTagTeam.RequestGameplayTag("CharacterConstructor.Team.A", true);

		StartLocation = TeamAObjectComponent->GetComponentLocation();
	}
	else
	{
		GameplayTagTeam.RequestGameplayTag("CharacterConstructor.Team.B", true);
		StartLocation = TeamBObjectComponent->GetComponentLocation();

	}
	GameplayTagContainer.AddTag(GameplayTagTeam);


	// int TypeClass : Mage = 0; Warrior = 1; Rogue =2;
	if (TypeClass == 0)
	{
		GameplayTagClass.RequestGameplayTag("CharacterConstructor.Class.Mage", true);
	}
	else if (TypeClass == 1)
	{
		GameplayTagClass.RequestGameplayTag("CharacterConstructor.Class.Rogue", true);
	}
	else if (TypeClass == 2)
	{
		GameplayTagClass.RequestGameplayTag("CharacterConstructor.Class.Warrior", true);
	}
	GameplayTagContainer.AddTag(GameplayTagClass);


	//Find into navigation   system result to spawn
	FNavLocation NavLocationResultSpawn;
	UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(StartLocation, 150.f, NavLocationResultSpawn);
	//NavLocationResultSpawn.Location
	//Spawn
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AAI_PortfolioChar* CreatedPawnAi = GetWorld()->SpawnActor<AAI_PortfolioChar>(PortfolioChar, TeamAObjectComponent->GetComponentLocation(), FRotator::ZeroRotator, ActorSpawnParameters);

	if (Command == 0)
	{
		CreatedPawnAi->GetMesh()->SetMaterial(0, ColorTeamA);
	}
	else
	{
		CreatedPawnAi->GetMesh()->SetMaterial(0, ColorTeamB);
	}

	if (!CreatedPawnAi)
	{
		UE_LOG(LogMiniGameTeam, Error, TEXT("CreatedPawnAi is NULL !"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "CreatedPawnAi is Null!");
		return;
	}//ExitIfNoValid

	GameplayTagContainer.AddTag(FGameplayTag::RequestGameplayTag("Status.CanMove", false));

	CreatedPawnAi->GetAbilitySystemComponent()->AddMinimalReplicationGameplayTags(GameplayTagContainer);
	FGameplayTagContainer TagContainer;


}
