// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimCharacter.h"

ASkyrimCharacter::ASkyrimCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASkyrimCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkyrimCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkyrimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

