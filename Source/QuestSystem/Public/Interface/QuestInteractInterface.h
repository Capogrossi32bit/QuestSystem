#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UQuestInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class QUESTSYSTEM_API IQuestInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};
