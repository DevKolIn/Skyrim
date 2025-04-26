// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimCameraMode_ThirdPerson.h"

#include "Curves/CurveVector.h"

USkyrimCameraMode_ThirdPerson::USkyrimCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TargetOffsetCurve = nullptr;
}

void USkyrimCameraMode_ThirdPerson::UpdateView(float DeltaTime)
{
	FVector PivotLocation = GetPivotLocation();
	FRotator PivotRotation = GetPivotRotation();

	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;

	// Apply third person offset using pitch.

	if (TargetOffsetCurve)
	{
		const FVector TargetOffset = TargetOffsetCurve->GetVectorValue(PivotRotation.Pitch);
		View.Location = PivotLocation + PivotRotation.RotateVector(TargetOffset);
	}
}
