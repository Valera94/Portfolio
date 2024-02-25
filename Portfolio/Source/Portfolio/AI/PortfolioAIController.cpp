// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

DEFINE_LOG_CATEGORY(LogPortfolioAI);

void APortfolioAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Tree->BlackboardAsset = BlackBoardData;

	//UBlackboardData& AssetBlackboard = *Tree->GetBlackboardAsset();
	//
	//FBlackboardEntry BlackboardEntry;
	//BlackboardEntry.KeyType = NewObject<UBlackboardKeyType_Vector>();
	//BlackboardEntry.EntryCategory = "TestCPP";
	//BlackboardEntry.EntryName = FName("TestCPPVector");
	//AssetBlackboard.Keys.Add(BlackboardEntry);

	if(!Tree)
	{
		UE_LOG(LogPortfolioAI, Warning, TEXT("BehaviorTree is empty ! "));
		return;
	}
	this->RunBehaviorTree(Tree);
}