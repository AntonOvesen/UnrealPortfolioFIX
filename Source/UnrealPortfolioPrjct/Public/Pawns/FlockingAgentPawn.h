// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlockingAgentPawn.generated.h"

UCLASS()
class UNREALPORTFOLIOPRJCT_API AFlockingAgentPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float AvoidanceRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float newMovePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XD")
		int neighbours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")
		float AlignmentWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")
		float CohesionWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")
		float AvoidanceWeight;

	TArray<AActor*> Actors;
	float avoidRadiusSquared;
	FVector lastMove;

	// Sets default values for this pawn's properties
	AFlockingAgentPawn();

protected:

	UFUNCTION(BlueprintNativeEvent)
		void AddActor(AActor* actor);
	void AddActor_Implementation(AActor* actor); 

	UFUNCTION(BlueprintNativeEvent)
		void RemoveActor(AActor* actor);
	void RemoveActor_Implementation(AActor* actor);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void GetCommonData();
	void GetCommonData_Implementation();

	void Move(FVector movement);

	// Behavior.
	FVector CombinedBehavior();

	UFUNCTION(BlueprintNativeEvent)
		FVector AlignmentBehavior();
	FVector AlignmentBehavior_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		FVector CohesionBehavior();
	FVector CohesionBehavior_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		FVector AvoidanceBehavior();
	FVector AvoidanceBehavior_Implementation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
