// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FlockingAgentBase.h"

// Sets default values
AFlockingAgentBase::AFlockingAgentBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlockingAgentBase::BeginPlay()
{
	Super::BeginPlay();
	avoidRadiusSquared = AvoidanceRadius * AvoidanceRadius;
}

// Called every frame
void AFlockingAgentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCommonData();

	Move(CombinedBehavior());
}

// Called to bind functionality to input
void AFlockingAgentBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFlockingAgentBase::GetCommonData()
{
	// Get array of type this inside overlap collider.
	GetOverlappingActors(Actors, AFlockingAgentBase::StaticClass());
}

void AFlockingAgentBase::Move(FVector movement)
{
	SetActorRotation(movement.Rotation(), ETeleportType::None);

	SetActorLocation(this->GetActorLocation() + (movement * Speed));
}

FVector AFlockingAgentBase::CombinedBehavior()
{
	FVector partialMove = FVector::ZeroVector;

	// Change this to change what behavior is run.
	partialMove += AlignmentBehavior() * AlignmentWeight;
	partialMove += CohesionBehavior() * CohesionWeight;
	partialMove += AvoidanceBehavior() * AvoidanceWeight;

	FVector move = partialMove.GetSafeNormal(0.001f);

	if (move == FVector::ZeroVector) {
		// Mf doesnt work yet.
		return lastMove;
	}

	lastMove = move;

	return move;
}

FVector AFlockingAgentBase::AlignmentBehavior()
{
	FVector direction = FVector::ZeroVector;

	for (AActor* actor : Actors) 
	{
		direction += actor->GetActorUpVector();
	}

	return direction.GetSafeNormal(0.001f);
}

FVector AFlockingAgentBase::CohesionBehavior()
{
	FVector target = FVector::ZeroVector;

	int nTarget = 0;

	for (AActor* actor : Actors) {
		target += actor->GetActorLocation();
		nTarget++;
	}

	if (nTarget > 0) 
	{
		// Get average location of targets.
		target /= nTarget;

		// Get move vector to target.
		target -= this->GetActorLocation();
	}

	return target.GetSafeNormal(0.001f);
}

FVector AFlockingAgentBase::AvoidanceBehavior()
{
	FVector partialMove = FVector::ZeroVector;

	for (AActor* actor : Actors) {

		FVector moveAway = this->GetActorLocation() - actor->GetActorLocation();

		if (moveAway.SizeSquared() < avoidRadiusSquared) {

			partialMove += moveAway;
		}
	}

	return partialMove.GetSafeNormal(0.001f);
}

