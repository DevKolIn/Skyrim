// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "SkyrimCameraComponent.generated.h"

class USkyrimCameraMode;
class USkyrimCameraModeStack;
class UObject;
struct FFrame;
struct FGameplayTag;
struct FMinimalViewInfo;
template <class TClass> class TSubclassOf;

DECLARE_DELEGATE_RetVal(TSubclassOf<USkyrimCameraMode>, FSkyrimCameraModeDelegate);

/**
 * 
 */
UCLASS()
class SKYRIM_API USkyrimCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	USkyrimCameraComponent(const FObjectInitializer& ObjectInitializer);
	
	static USkyrimCameraComponent* FindCameraComponent(APawn* InPawn) { return (InPawn != nullptr) ? InPawn->FindComponentByClass<USkyrimCameraComponent>() : nullptr; }

	// Returns the target actor that the camera is looking at.
	virtual AActor* GetTargetActor() const { return GetOwner(); }
	
	virtual void OnRegister() override;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	virtual void UpdateCameraModes();
	
public:
	// Delegate used to query for the best camera mode.
	FSkyrimCameraModeDelegate DetermineCameraModeDelegate;
	
protected:
	// Stack used to blend the camera modes.
	UPROPERTY()
	TObjectPtr<USkyrimCameraModeStack> CameraModeStack;

	// Offset applied to the field of view.  The offset is only for one frame, it gets cleared once it is applied.
	float FieldOfViewOffset;
};
