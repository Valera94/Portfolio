// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreator.h"

#include "DA_CharacterCreator.h"
#include "UW_CharacterCreator.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/AssetManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"

// Sets default values
ACharacterCreator::ACharacterCreator()
{
	bReplicates = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SceneComponent = Root
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	//SceneComponent = Decoration
	Decoration = CreateDefaultSubobject<UChildActorComponent>("Decoration");
	Decoration->SetupAttachment(Root);
	//SceneCapture
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
	SceneCaptureComponent->SetupAttachment(Root);
	//SkeletalMesh
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(Root);
}

void ACharacterCreator::BeginPlay()
{
	Super::BeginPlay();

	//SceneCapture
	//SceneCaptureComponent->ShowOnlyActorComponents();
	SceneCaptureComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	SceneCaptureComponent->ShowOnlyActors.Add(this);
	SceneCaptureComponent->ShowOnlyActors.Add(Decoration->GetChildActor());

	check(DataTableAsset);
	if (DataTableAsset == nullptr) { return; }	 //if no valid exit
	GetDataTableRow(0);
	if (UW_ClassCharacterCreator == nullptr) { return; } //if no valid exit

	CreateUW();

}

// Called when the game starts or when spawned

void ACharacterCreator::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, "Possessed");
}

void ACharacterCreator::UnPossessed()
{
	Super::UnPossessed();
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, "UnPossessed");

	Destroy();
}


void ACharacterCreator::CreateUW()
{

	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FSoftObjectPath Reference = UW_ClassCharacterCreator.ToString();
	ACharacterCreator* Self = this;

	AssetLoader.RequestAsyncLoad(Reference, FStreamableDelegate::CreateLambda(
		[Reference, Self]()
		{
			UClass* WidgetType = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *(Reference.ToString())));
			UUserWidget* UserWidget = CreateWidget<UUserWidget>(Self->GetWorld(), WidgetType, *(WidgetType->GetName()));
			Self->InformationAboutWidget.UserWidget = Cast<UUW_CharacterCreator>(UserWidget);
			Self->InformationAboutWidget.UserWidget->AddToViewport();
			Self->InformationAboutWidget.UserWidget->AddToVerticalBox_Race(Self->MaterialInstance_Race, Self->DataTableAsset);
			Self->InformationAboutWidget.UserWidget->AddToHorizontalBox_Gender(Self->MaterialInstance_Gender);
			Self->InformationAboutWidget.UserWidget->AddToHorizontalBox_Class(Self->MaterialInstance_Class, &Self->RowDataTable);
			Self->InformationAboutWidget.UserWidget->CharacterCreator = Self;
			Self->InformationAboutWidget.UserWidget->SimpleClicked();
		}));

}

void ACharacterCreator::RecreateImageClass()
{
	InformationAboutWidget.UserWidget->HorizontalBox_Class->ClearChildren();
	InformationAboutWidget.UserWidget->AddToHorizontalBox_Class(MaterialInstance_Class, &RowDataTable);
}

void ACharacterCreator::GetDataTableRow(const int32 IndexSelect)
{
	RowDataTable = *Cast<UDataTable>(DataTableAsset)->FindRow<FDataTableCharacterCreator>(
		DataTableAsset->GetRowNames()[IndexSelect],
		nullptr,
		false);
}


bool ACharacterCreator::FChangeRace(const int32 IndexSelect)
{
	GetDataTableRow(IndexSelect);

	if (InformationAboutWidget.IndexRace != IndexSelect)
	{
		InformationAboutWidget.IndexRace = IndexSelect;
		RecreateImageClass();

		Cast<UUW_General_AroundButton>(InformationAboutWidget.UserWidget->HorizontalBox_Class->GetChildAt(0))->BackCallOnClick();


	}

	if (RowDataTable.struct_Race.DecorationActor != nullptr)
	{

		Decoration->SetChildActorClass(RowDataTable.struct_Race.DecorationActor);
		SceneCaptureComponent->ShowOnlyActors.Add(Decoration->GetChildActor());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, *Decoration->GetChildActorClass()->GetName());

	}

	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);

	for (const auto& WidgetWithInterface : OutWidgets)
	{
		UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
		if (L_UW_CharacterCreator != nullptr)
		{
			L_UW_CharacterCreator->FReturnRowDataTable(RowDataTable);
			L_UW_CharacterCreator->FChangeText(2, RowDataTable.struct_Race.AtlasMaterial.TextInfo.TopText, RowDataTable.struct_Race.AtlasMaterial.TextInfo.InfoText);
		}
	}

	FChangeClass(0);
	FChangeGender(0);

	return true;
}

bool ACharacterCreator::FChangeClass(const int32 IndexSelect)
{
	InformationAboutWidget.IndexClass = IndexSelect;

	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);

	// 0 - CLass, 1 - Gender, 2 - Race
	for (const auto& WidgetWithInterface : OutWidgets)
	{
		UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
		if (L_UW_CharacterCreator != nullptr) { L_UW_CharacterCreator->FChangeText(0, RowDataTable.struct_Class[IndexSelect].AtlasMaterial.TextInfo.TopText, RowDataTable.struct_Class[IndexSelect].AtlasMaterial.TextInfo.InfoText); }
	}
	FChangeGender(0);
	return true;
}

bool ACharacterCreator::FChangeGender(const int32 IndexSelect)
{
	InformationAboutWidget.IndexGender = IndexSelect;
	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);


	if (IndexSelect == 1)
	{
		SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh>(RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.SkeletalMeshWomen.LoadSynchronous()));
		for (const auto& WidgetWithInterface : OutWidgets)
		{
			UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
			if (L_UW_CharacterCreator != nullptr) {
				L_UW_CharacterCreator->FChangeText(1, RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.TextInfoWomen.TopText,
					RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.TextInfoWomen.InfoText);
			}
		}
	}
	else  if (IndexSelect == 0)
	{
		SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh>(RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.SkeletalMeshMan.LoadSynchronous()));
		for (const auto& WidgetWithInterface : OutWidgets)
		{
			UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
			if (L_UW_CharacterCreator != nullptr) {
				L_UW_CharacterCreator->FChangeText(1, RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.TextInfoMan.TopText,
					RowDataTable.struct_Class[InformationAboutWidget.IndexClass].UniqueViewForClass.TextInfoMan.InfoText);
			}
		}
	}
	return true;
}

void ACharacterCreator::Server_PossessClient_Implementation(APlayerController* ThisController, const FInformationAboutWidget& SetInformationAboutWidget, const FDataTableCharacterCreator& DataTableCharacter)
{

	TArray<AActor*>LSpawnLocation;
	UGameplayStatics::GetAllActorsOfClass(ThisController->GetWorld(), APlayerStart::StaticClass(), LSpawnLocation);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACharacter* CreatedActor = ThisController->GetWorld()->SpawnActor<ACharacter>(DataTableCharacter.struct_Class[InformationAboutWidget.IndexClass].ClassForSpawnAndPossess, LSpawnLocation[0]->GetActorTransform(), SpawnParameters);




	//0 = Mam ; 1 = Woman GENDER WITH ANIMATION
	if (SetInformationAboutWidget.IndexGender == 0)
	{
		Cast<APortfolioCharacterAbility>(CreatedActor)->ViewSkeletalMesh = DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueViewForClass.SkeletalMeshMan.LoadSynchronous();
		Cast<APortfolioCharacterAbility>(CreatedActor)->AnimationSkeletalMesh = DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueViewForClass.AnimationBlueprint;

	}
	else
	{
		Cast<APortfolioCharacterAbility>(CreatedActor)->ViewSkeletalMesh = (RowDataTable.struct_Class[SetInformationAboutWidget.IndexClass].UniqueViewForClass.SkeletalMeshWomen.LoadSynchronous());
		Cast<APortfolioCharacterAbility>(CreatedActor)->AnimationSkeletalMesh = RowDataTable.struct_Class[SetInformationAboutWidget.IndexClass].UniqueViewForClass.AnimationBlueprint;
	}

	AddGASInformation(
		CreatedActor,
		DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueClassSkill.ArrAttribute,
		DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueClassSkill.ArrEffect,
		DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueClassSkill.ArrAbility,
		DataTableCharacter.struct_Class[SetInformationAboutWidget.IndexClass].UniqueClassSkill.GameplayTagContainer);

	AddGASInformation(
		CreatedActor,
		DataTableCharacter.struct_Race.UniqueRaceSkill.ArrAttribute,
		DataTableCharacter.struct_Race.UniqueRaceSkill.ArrEffect,
		DataTableCharacter.struct_Race.UniqueRaceSkill.ArrAbility,
		DataTableCharacter.struct_Race.UniqueRaceSkill.GameplayTagContainer);

	ThisController->Possess(CreatedActor);
}

void ACharacterCreator::AddGASInformation(ACharacter*& SpawnedCharacter, const TArray<FStructAttribute>& SetArrAttribute, const TArray<FStructEffect>& SetArrEffect, const TArray<FStructAbility>& SetArrAbility, const FGameplayTagContainer& SetTagContainer)
{

	if (!SetArrAttribute.IsEmpty())
	{
		for (const auto& i : SetArrAttribute)
		{
			if (i.Attribute != nullptr)
			{
				UAttributeSet* AttributeSet = NewObject<UAttributeSet>(Cast<APortfolioCharacterAbility>(SpawnedCharacter)->GetAbilitySystemComponent()->GetOwnerActor(), i.Attribute);
				Cast<APortfolioCharacterAbility>(SpawnedCharacter)->GetAbilitySystemComponent()->AddAttributeSetSubobject<UAttributeSet>(AttributeSet);
			}
		}
	}

	if (!SetArrAbility.IsEmpty())
	{
		for (const auto& i : SetArrAbility)
		{
			if (i.Ability != nullptr)
			{
				Cast<APortfolioCharacterAbility>(SpawnedCharacter)->DefaultAbility.Add(i.Ability);
			}
		}

	}

	if (!SetArrEffect.IsEmpty())
	{
		for (const auto& i : SetArrEffect)
		{
			if (i.Effect != nullptr)
			{
				Cast<APortfolioCharacterAbility>(SpawnedCharacter)->DefaultEffects.AddUnique(i.Effect);
			}
		}

	}

	if (!SetTagContainer.IsEmpty())
	{
		Cast<APortfolioCharacterAbility>(SpawnedCharacter)->GetAbilitySystemComponent()->AddReplicatedLooseGameplayTags(SetTagContainer);
	}
}

bool ACharacterCreator::FClickComplete()
{

	Server_PossessClient(GetLocalViewingPlayerController(),
		InformationAboutWidget, RowDataTable);

	return false;
}