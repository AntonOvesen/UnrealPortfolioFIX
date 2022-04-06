// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FlockingAgentPawn.h"

// Sets default values
AFlockingAgentPawn::AFlockingAgentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockingAgentPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlockingAgentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCommonData();

	Move(CombinedBehavior());

}

// Called to bind functionality to input
void AFlockingAgentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFlockingAgentPawn::GetCommonData()
{
	// Get array of type this inside overlap collider.
	GetOverlappingActors(Actors, AFlockingAgentPawn::StaticClass());
}

void AFlockingAgentPawn::Move(FVector movement)
{
	SetActorRotation(movement.Rotation(), ETeleportType::None);

	SetActorLocation(this->GetActorLocation() + (movement * Speed));
}

FVector AFlockingAgentPawn::CombinedBehavior()
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

void AFlockingAgentPawn::Test123_Implementation() {

}

FVector AFlockingAgentPawn::AlignmentBehavior_Implementation()
{
	FVector direction = FVector::ZeroVector;

	for (AActor* actor : Actors)
	{
		direction += actor->GetActorUpVector();
	}

	return direction.GetSafeNormal(0.001f);
}

FVector AFlockingAgentPawn::CohesionBehavior_Implementation()
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

FVector AFlockingAgentPawn::AvoidanceBehavior_Implementation()
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