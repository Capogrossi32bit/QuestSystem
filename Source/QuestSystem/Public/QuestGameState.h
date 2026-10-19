#pragma once

//10. GameState
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "QuestTypes.h"
#include "QuestGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnGameplayObjectiveEvent,
	EQuestObjectiveType, ObjectiveType,
	FName, TargetID,
	int32, Amount
);

UCLASS()
class QUESTSYSTEM_API AQuestGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	// PROPERTIES
	UPROPERTY(BlueprintAssignable, Category = "QuestSystem|Events")
	FOnGameplayObjectiveEvent OnGameplayObjectiveEvent;

	// FUNCTIONS
	//11. Funcion ReportGameplayObjective
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);

};


