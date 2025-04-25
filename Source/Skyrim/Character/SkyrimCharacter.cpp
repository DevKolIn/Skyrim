// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimCharacter.h"

#include "SkyrimPawnExtensionComponent.h"

ASkyrimCharacter::ASkyrimCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	PawnExtComponent = CreateDefaultSubobject<USkyrimPawnExtensionComponent>(TEXT("PawnExtenstionComponent"));
}

void ASkyrimCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkyrimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

