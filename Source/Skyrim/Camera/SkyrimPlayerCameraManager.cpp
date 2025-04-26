// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimPlayerCameraManager.h"

ASkyrimPlayerCameraManager::ASkyrimPlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultFOV = SKYRIM_CAMERA_DEFAULT_FOV;
	DefaultPitch_MIN = SKYRIM_CAMERA_DEFAULT_PITCH_MIN;
	DefaultPitch_MAX = SKYRIM_CAMERA_DEFAULT_PITCH_MAX;
}
