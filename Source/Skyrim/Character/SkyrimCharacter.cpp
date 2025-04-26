// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimCharacter.h"

#include "SkyrimPawnExtensionComponent.h"
#include "Skyrim/Camera/SkyrimCameraComponent.h"

ASkyrimCharacter::ASkyrimCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	PawnExtComponent = CreateDefaultSubobject<USkyrimPawnExtensionComponent>(TEXT("PawnExtenstionComponent"));

	{
		CameraComponent = CreateDefaultSubobject<USkyrimCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));
	}
}

void ASkyrimCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkyrimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

