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

	avoidRadiusSquared = AvoidanceRadius * AvoidanceRadius;
	lastMove = FVector::UpVector;
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

void AFlockingAgentPawn::GetCommonData_Implementation()
{
	// Get array of type this inside overlap collider.
	GetOverlappingActors(Actors, AFlockingAgentPawn::StaticClass());


	/*neighbours = 0;
	for (AActor* actor : Actors) {
		neighbours++;
	}*/
}

void AFlockingAgentPawn::Move(FVector movement)
{
	FRotator MyRotator = FRotationMatrix::MakeFromZ(movement).Rotator();
	FQuat xd = MyRotator.Quaternion();
	SetActorRotation(MyRotator, ETeleportType::None);

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
		neighbours = 1;
		
		lastMove.Normalize();
		lastMove *= Speed;
		return lastMove;
	}

	if (lastMove != FVector::ZeroVector) {
		move = lastMove + ((move / 100) * newMovePower);
	}

	neighbours = 0;

	lastMove = move;

	move.Normalize();

	FVector move2 = move.GetSafeNormal(0.001f);

	return move;
}

FVector AFlockingAgentPawn::AlignmentBehavior_Implementation()
{
	FVector direction = FVector::ZeroVector;

	for (AActor* actor : Actors)
	{
		direction += actor->GetActorUpVector();
	}

	direction.Normalize();

	return direction;
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

	target.Normalize();

	return target;
}

FVector AFlockingAgentPawn::AvoidanceBehavior_Implementation()
{
	FVector partialMove = FVector::ZeroVector;

	int nAvoid = 0;

	for (AActor* actor : Actors) {

		FVector moveAway = this->GetActorLocation() - actor->GetActorLocation();

		if (moveAway.SizeSquared() < avoidRadiusSquared) {

			partialMove += moveAway;
			nAvoid++;
		}
	}

	if (nAvoid > 0) {
		partialMove /= nAvoid;
	}

	partialMove.Normalize();

	return partialMove;

	//FVector safeNormal = partialMove.Normalize();

	//neighbours = safeNormal.Size() * 100;
	//neighbours = nAvoid;

	
}