// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreator.h"

#include "DA_CharacterCreator.h"
#include "UW_CharacterCreator.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include <Net\UnrealNetwork.h>

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
	Decoration = CreateDefaultSubobject<USceneComponent>("Decoration");
	Decoration->SetupAttachment(Root);
	//SceneCapture
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
	SceneCaptureComponent->SetupAttachment(Root);
	//SkeletalMesh
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACharacterCreator::BeginPlay()
{
	Super::BeginPlay();
	//SceneCapture
	SceneCaptureComponent->ShowOnlyActorComponents(this, false);

	check(DataTableAsset);
	if (DataTableAsset == nullptr) { return; }	 //if no valid exit
	GetDataTableRow(0);
	if (UW_ClassCharacterCreator == nullptr) { return; } //if no valid exit

	CreateUW();


}



void ACharacterCreator::CreateUW()
{

	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FSoftObjectPath Reference = UW_ClassCharacterCreator.ToString();
	TSoftObjectPtr<UMaterialInstance> L_MaterialInstance_Race = MaterialInstance_Race;
	TSoftObjectPtr<UMaterialInstance> L_MaterialInstance_Class = MaterialInstance_Class;
	TSoftObjectPtr<UMaterialInstance> L_MaterialInstance_Gender = MaterialInstance_Gender;
	ACharacterCreator* Self = this;

	UDataTable* DataTable = DataTableAsset;
	FDataTableCharacterCreator* LRowDataTable = &RowDataTable;

	AssetLoader.RequestAsyncLoad(Reference, FStreamableDelegate::CreateLambda([Reference, Self, LRowDataTable, L_MaterialInstance_Race, L_MaterialInstance_Gender, L_MaterialInstance_Class, DataTable]()
		{
			UClass* WidgetType = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *(Reference.ToString())));

			UUserWidget* UserWidget = CreateWidget<UUserWidget>(Self->GetWorld(), WidgetType, *(WidgetType->GetName()));
			UserWidget->AddToViewport();
			Cast<UUW_CharacterCreator>(UserWidget)->AddToVerticalBox_Race(L_MaterialInstance_Race, DataTable);
			Cast<UUW_CharacterCreator>(UserWidget)->AddToHorizontalBox_Gender(L_MaterialInstance_Gender);
			Cast<UUW_CharacterCreator>(UserWidget)->AddToHorizontalBox_Class(L_MaterialInstance_Class, LRowDataTable);

			Cast<UUW_CharacterCreator>(UserWidget)->CharacterCreator = Self;
			Cast<UUW_CharacterCreator>(UserWidget)->SimpleClicked();

		}));


}

void ACharacterCreator::ConstructorCharacter()
{
	UAC_PortfolioAbilitySystem* L_CompAbility = Cast<UAC_PortfolioAbilitySystem>(Cast<APortfolioCharacterAbility>(CharacterForBackView)->GetAbilitySystemComponent());
	FGameplayTagContainer TagContainer;

	if (TagClass.GetTagName() == FName("Ability.CharacterConstructor.Class.Mage"))
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Class.Mage")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.TypeOfArmor.Cloth")));

		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Energy")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Health")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Mana")));

	}
	else if (TagClass.GetTagName() == FName("Ability.CharacterConstructor.Class.Rogue"))
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Class.Mage")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.TypeOfArmor.Cloth")));

		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Energy")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Health")));
	}
	else if (TagClass.GetTagName() == FName("Ability.CharacterConstructor.Class.Warrior"))
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Class.Mage")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.TypeOfArmor.Cloth")));

		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Energy")));
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.CharacterConstructor.Attribute.Health")));
	}

	L_CompAbility->AddLooseGameplayTags(TagContainer, 1);
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

	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);

	for (const auto& WidgetWithInterface : OutWidgets)
	{
		UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
		if (L_UW_CharacterCreator != nullptr)
		{
			L_UW_CharacterCreator->FReturnRowDataTable(RowDataTable);
			L_UW_CharacterCreator->FChangeText(2, RowDataTable.struct_Race.TextInfo.TopText, RowDataTable.struct_Race.TextInfo.InfoText);
		}


	}
	return true;
}

bool ACharacterCreator::FChangeGender(const int32 IndexSelect)
{
	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);


	if (IndexSelect == 1)
	{
		SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh> (RowDataTable.struct_Gender.SkeletalMeshWomen.LoadSynchronous()));
		for (const auto& WidgetWithInterface : OutWidgets)
		{
			UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
			if (L_UW_CharacterCreator != nullptr) { L_UW_CharacterCreator->FChangeText(1, RowDataTable.struct_Gender.TextInfoWomen.TopText, RowDataTable.struct_Gender.TextInfoWomen.InfoText); }
		}

	}
	else  if (IndexSelect == 0)
	{
		SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh>(RowDataTable.struct_Gender.SkeletalMeshMan.LoadSynchronous()));
		for (const auto& WidgetWithInterface : OutWidgets)
		{
			UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
			if (L_UW_CharacterCreator != nullptr) { L_UW_CharacterCreator->FChangeText(1, RowDataTable.struct_Gender.TextInfoMan.TopText, RowDataTable.struct_Gender.TextInfoMan.InfoText); }
		}

	}
	return false;


}


bool ACharacterCreator::FChangeClass(const int32 IndexSelect)
{

	TArray<UUserWidget*> OutWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), OutWidgets, UInterfaceCharacterCreator::StaticClass(), false);

	// 0 - CLass, 1 - Gender, 2 - Race
	for (const auto& WidgetWithInterface : OutWidgets)
	{
		UUW_CharacterCreator* L_UW_CharacterCreator = Cast<UUW_CharacterCreator>(WidgetWithInterface);
		if (L_UW_CharacterCreator != nullptr) { L_UW_CharacterCreator->FChangeText(0, RowDataTable.struct_Class[IndexSelect].TextInfo.TopText, RowDataTable.struct_Class[IndexSelect].TextInfo.InfoText); }
		TagClass = RowDataTable.struct_Class[IndexSelect].TextInfo.GameplayTag;
	}

	return false;
}

bool ACharacterCreator::FClickComplete()
{
	if (CharacterForBackView==nullptr && SkeletalMeshComponent==nullptr) { return false; }
	ConstructorCharacter(); // Add needed Tag
	//Cast<APortfolioCharacter>(CharacterForBackView)->Server_ChangeSkeletalMesh_Implementation(SkeletalMeshComponent->GetSkeletalMeshAsset());
	GetNetOwningPlayer()->GetPlayerController(GetWorld())->SetViewTargetWithBlend(Cast<AActor>(CharacterForBackView));
	//Cast<APortfolioCharacter>(CharacterForBackView)->Server_ChangeMesh(SkeletalMeshComponent->SkeletalMesh);   Old
	Cast<APortfolioCharacter>(CharacterForBackView)->Server_ChangeMesh(SkeletalMeshComponent->GetSkeletalMeshAsset()); //New
	Destroy();
	return false;
}
