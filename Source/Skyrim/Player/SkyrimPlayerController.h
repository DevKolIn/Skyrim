// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkyrimPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SKYRIM_API ASkyrimPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASkyrimPlayerController(const FObjectInitializer& ObjectInitializer);
};
