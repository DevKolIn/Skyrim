// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimPlayerController.h"

#include "Skyrim/Camera/SkyrimPlayerCameraManager.h"

ASkyrimPlayerController::ASkyrimPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ASkyrimPlayerCameraManager::StaticClass();
}
