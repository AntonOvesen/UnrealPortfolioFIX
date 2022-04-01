// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UPPCharacter.h"

// Sets default values
AUPPCharacter::AUPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

