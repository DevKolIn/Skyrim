// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyrimCameraMode.generated.h"

class AActor;
class USkyrimCameraComponent;
/**
 * ELyraCameraModeBlendFunction
 *
 *	Blend function used for transitioning between camera modes.
 */
UENUM(BlueprintType)
enum class ESkyrimameraModeBlendFunction : uint8
{
	// Does a simple linear interpolation.
	Linear,

	// Immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by the exponent.
	EaseIn,

	// Smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by the exponent.
	EaseOut,

	// Smoothly accelerates and decelerates.  Ease amount controlled by the exponent.
	EaseInOut,

	COUNT	UMETA(Hidden)
};

/**
 * FLyraCameraModeView
 *
 *	View data produced by the camera mode that is used to blend camera modes.
 */
struct FSkyrimCameraModeView
{
public:
	FSkyrimCameraModeView();

	void Blend(const FSkyrimCameraModeView& Other, float OtherWeight);

public:
	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class SKYRIM_API USkyrimCameraMode : public UObject
{
	GENERATED_BODY()

public:
	USkyrimCameraMode(const FObjectInitializer& ObjectInitializer);

	USkyrimCameraComponent* GetSkyrimCameraComponent() const;
	
	AActor* GetTargetActor() const;

	const FSkyrimCameraModeView& GetCameraModeView() const { return View; }
	
	// Called when this camera mode is activated on the camera mode stack.
	virtual void OnActivation() {};

	// Called when this camera mode is deactivated on the camera mode stack.
	virtual void OnDeactivation() {};

	void UpdateCameraMode(float DeltaTime);
	
protected:
	virtual FVector GetPivotLocation() const;
	virtual FRotator GetPivotRotation() const;
	
	virtual void UpdateView(float DeltaTime);
	virtual void UpdateBlending(float DeltaTime);
	
/* Blend */
public:
	float GetBlendTime() const { return BlendTime; }
	float GetBlendWeight() const { return BlendWeight; }
	void SetBlendWeight(float Weight);
	
protected:
	// How long it takes to blend in this mode.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;

	// Function used for blending.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	ESkyrimameraModeBlendFunction BlendFunction;
	
	// Exponent used by blend functions to control the shape of the curve.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendExponent;
	
	// Linear blend alpha used to determine the blend weight.
	float BlendAlpha;

	// Blend weight calculated using the blend alpha and function.
	float BlendWeight;

/* View */
protected:
	// View output produced by the camera mode.
	FSkyrimCameraModeView View;

	// The horizontal field of view (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	// Minimum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMin;

	// Maximum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMax;
};


/**
 * ULyraCameraModeStack
 *
 *	스택를 통해 카메라 블렌딩에 사용
 */
UCLASS()
class USkyrimCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	USkyrimCameraModeStack(const FObjectInitializer& ObjectInitializer);

	void PushCameraMode(TSubclassOf<USkyrimCameraMode> CameraModeClass);
	bool EvaluateStack(float DeltaTime, FSkyrimCameraModeView& OutCameraModeView);

protected:
	USkyrimCameraMode* GetCameraModeInstance(TSubclassOf<USkyrimCameraMode> CameraModeClass);

	void UpdateStack(float DeltaTime);
	void BlendStack(FSkyrimCameraModeView& OutCameraModeView) const;
	
protected:
	bool bIsActive;
	
	/* 생성된 CameraMode를 관리 */
	UPROPERTY()
	TArray<TObjectPtr<USkyrimCameraMode>> CameraModeInstances;

	/* Camera Matrix Blend 업데이트 진행 큐 */
	UPROPERTY()
	TArray<TObjectPtr<USkyrimCameraMode>> CameraModeStack;
};
