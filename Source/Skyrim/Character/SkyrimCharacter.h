// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SkyrimCharacter.generated.h"

class USkyrimPawnExtensionComponent;

UCLASS()
class SKYRIM_API ASkyrimCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkyrimCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/*  */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkyrimPawnExtensionComponent> PawnExtComponent;
};
