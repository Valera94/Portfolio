// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlace.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Portfolio/AI/MiniGameTeam.h"
#include <BehaviorTree\Blackboard\BlackboardKeyType_Object.h>

#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_FindPlace::UBTTask_FindPlace()
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//RefMiniGameTeam;
	AMiniGameTeam* RefMiniGameTeam = Cast<AMiniGameTeam>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(ActorMiniGameTeam.SelectedKeyName));
	const	FVector RefLocationTeamA = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(LocationTeamA.SelectedKeyName);
	const	FVector RefLocationTeamB = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(LocationTeamB.SelectedKeyName);
	


	//If No Valid Exit and Faild Result
	if (!RefMiniGameTeam)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return  EBTNodeResult::Failed;
	}

	//if visible - we move to sphere and try get and move back;
	//if hidden - we find who get this sphere and try get self if he enemy team or cover if he is friend

	if (RefMiniGameTeam->GetSphere()->IsVisible())
	{

		//He is no attached

		const float DistanceToSphere = UKismetMathLibrary::Vector_Distance(RefMiniGameTeam->GetSphere()->GetComponentLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetRootComponent()->GetComponentLocation());
		if (DistanceToSphere >= 100)
		{
			//Move to Sphere

			OwnerComp.GetAIOwner()->MoveToLocation(RefMiniGameTeam->GetSphere()->GetComponentLocation(), 5.f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return  EBTNodeResult::Failed;
		}
		else
		{

			//Attach Sphere to self

			RefMiniGameTeam->GetSphere()->AttachToComponent(OwnerComp.GetAIOwner()->GetPawn()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			RefMiniGameTeam->GetSphere()->SetHiddenInGame(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return  EBTNodeResult::Succeeded;

			//End He is attached to AI end he is hidden for game view
		}

	}
	else
	{
		if (RefMiniGameTeam->GetSphere()->GetAttachParentActor() == OwnerComp.GetAIOwner()->GetPawn())
		{

			// We try move to self base
			const float DistanceToBase = UKismetMathLibrary::Vector_Distance(RefLocationTeamA, OwnerComp.GetAIOwner()->GetPawn()->GetRootComponent()->GetComponentLocation());

			if (DistanceToBase<80.f)
			{
				//Set Default
				RefMiniGameTeam->GetSphere()->AttachToComponent(RefMiniGameTeam->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
				RefMiniGameTeam->GetSphere()->SetRelativeLocation(FVector::Zero());
				RefMiniGameTeam->GetSphere()->SetHiddenInGame(false);
				RefMiniGameTeam->AddScoreTeamA();

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;

			}
			else
			{
				OwnerComp.GetAIOwner()->MoveToLocation(RefLocationTeamA, 10.f);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}

		}
		else
		{

			//We try cover our char

			//If we near we go back from this AI
			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
			FNavLocation NavLocation;
			if(NavSystem->GetRandomPointInNavigableRadius(RefMiniGameTeam->GetSphere()->GetComponentLocation(),200.f, NavLocation))
			{
				OwnerComp.GetAIOwner()->MoveToLocation(NavLocation.Location, 10.f);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}
				

		}
	}
	
	return  EBTNodeResult::Failed;
}