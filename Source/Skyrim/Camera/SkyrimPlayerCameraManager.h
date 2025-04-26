// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SkyrimPlayerCameraManager.generated.h"


#define SKYRIM_CAMERA_DEFAULT_FOV (80.0f)
#define SKYRIM_CAMERA_DEFAULT_PITCH_MIN (-89.0f)
#define SKYRIM_CAMERA_DEFAULT_PITCH_MAX (89.0f)

/**
 * 
 */
UCLASS()
class SKYRIM_API ASkyrimPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ASkyrimPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

private:
	float DefaultFOV;
	float DefaultPitch_MIN;
	float DefaultPitch_MAX;
};
