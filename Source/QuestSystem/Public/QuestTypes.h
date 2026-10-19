#pragma once

#include "CoreMinimal.h"
#include "QuestTypes.generated.h"

// Forward declaration de UQuestDefinition
class UQuestDefinition;

// 1.Enum de tipos de objetivo

/*
Kill
Collect
Interact
ReachLocation
*/

UENUM(BlueprintType)
enum class EQuestObjectiveType : uint8
{
	Kill UMETA(DisplayName = "Kill"),
	Collect UMETA(DisplayName = "Collect"),
	Interact UMETA(DisplayName = "Interact"),
	ReachLocation UMETA(DisplayName = "ReachLocation")
};

// 2.Struct de objetivo

/*
ST_QuestObjective
ObjectiveID – Name
ObjectiveType – EQuestObjectiveType
TargetID – Name
RequiredAmount – Integer
CurrentAmount – Integer
*/

USTRUCT(BlueprintType)
struct FQuestObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ObjectiveID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount;
};


// 4. Struct de Quest Runtime
/*
QuestID – Name
QuestDefinition – PDA_QuestDefinition Object Reference
Objectives – Array<ST_QuestObjective>
IsActive – Boolean
IsCompleted – Boolean
*/

USTRUCT(BlueprintType)
struct FQuestRuntime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UQuestDefinition> QuestDefinition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCompleted = false;
};