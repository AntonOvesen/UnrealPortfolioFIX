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

}

// Called to bind functionality to input
void AFlockingAgentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

