// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "../SkyrimGameplayTags.h"
#include "SkyrimPawnExtensionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYRIM_API USkyrimPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
public:
	USkyrimPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

/* IGameFrameworkInitStateInterface */
public:
	/** The name of this component-implemented feature */
	static const FName NAME_ActorFeatureName;
	
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }

	//~ Begin IGameFrameworkInitStateInterface interface
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface
};
