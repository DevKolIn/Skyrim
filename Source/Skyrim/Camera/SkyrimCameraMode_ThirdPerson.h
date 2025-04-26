// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyrimCameraMode.h"
#include "SkyrimCameraMode_ThirdPerson.generated.h"


class UCurveVector;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SKYRIM_API USkyrimCameraMode_ThirdPerson : public USkyrimCameraMode
{
	GENERATED_BODY()

public:
	USkyrimCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void UpdateView(float DeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	TObjectPtr<const UCurveVector> TargetOffsetCurve;
};
