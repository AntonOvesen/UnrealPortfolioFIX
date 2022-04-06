// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FlockingAgentPawnNew.h"

// Sets default values
AFlockingAgentPawnNew::AFlockingAgentPawnNew()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockingAgentPawnNew::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlockingAgentPawnNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlockingAgentPawnNew::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

