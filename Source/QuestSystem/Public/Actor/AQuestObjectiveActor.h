// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestTypes.h"
#include "Public/Interface/QuestInteractInterface.h"
#include "AQuestObjectiveActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class QUESTSYSTEM_API AAQuestObjectiveActor : public AActor, public IQuestInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAQuestObjectiveActor();
	
	// UPROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	EQuestObjectiveType ObjectiveType = EQuestObjectiveType::Interact;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName TargetID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int32 Amount = 1;


	// FUNCTION
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ReportObjective();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

private:
	bool bAlreadyReported = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
