// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SkyrimCharacter.generated.h"

UCLASS()
class SKYRIM_API ASkyrimCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkyrimCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
