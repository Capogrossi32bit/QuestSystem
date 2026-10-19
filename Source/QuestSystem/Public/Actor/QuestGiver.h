#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Interface/QuestInteractInterface.h"
#include "QuestGiver.generated.h"

class UQuestDefinition;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class QUESTSYSTEM_API AQuestGiver : public AActor, public IQuestInteractInterface
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AQuestGiver();

	//PROPERTIES

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> QuestMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UQuestDefinition> QuestDefinition = nullptr;

	//FUNCTIONS
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
