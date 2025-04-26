// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimHeroComponent.h"

#include "SkyrimPawnExtensionComponent.h"
#include "Skyrim/SkyrimLogChannel.h"
#include "Skyrim/Player/SkyrimPlayerController.h"
#include "Skyrim/Player/SkyrimPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Skyrim/Camera/SkyrimCameraComponent.h"

const FName USkyrimHeroComponent::NAME_ActorFeatureName("Hero");

USkyrimHeroComponent::USkyrimHeroComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void USkyrimHeroComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetPawn<APawn>())
	{
		UE_LOG(LogSkyrim, Error, TEXT("[USkyrimHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));
	}

	RegisterInitStateFeature();
}

void USkyrimHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(USkyrimPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(SkyrimGameplayTags::InitState_Spawned));
	
	CheckDefaultInitialization();
}

void USkyrimHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

bool USkyrimHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	if (!CurrentState.IsValid() && DesiredState == SkyrimGameplayTags::InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == SkyrimGameplayTags::InitState_Spawned && DesiredState == SkyrimGameplayTags::InitState_DataAvailable)
	{
		if (GetPlayerState<ASkyrimPlayerState>() == nullptr)
		{
			return false;
		}
		
		AController* Controller = GetController<AController>();

		const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
			(Controller->PlayerState != nullptr) && \
			(Controller->PlayerState->GetOwner() == Controller);

		if (!bHasControllerPairedWithPS)
		{
			return false;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const bool bIsBot = Pawn->IsBotControlled();

		if (bIsLocallyControlled && !bIsBot)
		{
			ASkyrimPlayerController* LyraPC = GetController<ASkyrimPlayerController>();

			// The input component and local player is required when locally controlled.
			if (!Pawn->InputComponent || !LyraPC || !LyraPC->GetLocalPlayer())
			{
				return false;
			}
		}

		return true;
	}
	else if (CurrentState == SkyrimGameplayTags::InitState_DataAvailable && DesiredState == SkyrimGameplayTags::InitState_DataInitialized)
	{
		// Wait for player state and extension component
		ASkyrimPlayerState* SkyrimPS = GetPlayerState<ASkyrimPlayerState>();

		return SkyrimPS && Manager->HasFeatureReachedInitState(Pawn, USkyrimPawnExtensionComponent::NAME_ActorFeatureName, SkyrimGameplayTags::InitState_DataInitialized);
	}
	else if (CurrentState == SkyrimGameplayTags::InitState_DataInitialized && DesiredState == SkyrimGameplayTags::InitState_GameplayReady)
	{
		// TODO add ability initialization checks?
		return true;
	}

	return false;
}

void USkyrimHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == SkyrimGameplayTags::InitState_DataAvailable && DesiredState == SkyrimGameplayTags::InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		ASkyrimPlayerState* SkyrimPS = GetPlayerState<ASkyrimPlayerState>();
		if (!ensure(Pawn && SkyrimPS))
		{
			return;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		// Hook up the delegate for all pawns, in case we spectate later
		if (bIsLocallyControlled)
		{
			if (USkyrimCameraComponent* CameraComponent = USkyrimCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		} 
	}
}

void USkyrimHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == USkyrimPawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == SkyrimGameplayTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}

void USkyrimHeroComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { SkyrimGameplayTags::InitState_Spawned, SkyrimGameplayTags::InitState_DataAvailable, SkyrimGameplayTags::InitState_DataInitialized, SkyrimGameplayTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

TSubclassOf<USkyrimCameraMode> USkyrimHeroComponent::DetermineCameraMode() const
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (USkyrimPawnExtensionComponent* PawnExtComp = USkyrimPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		return DefaultCameraMode;
	}

	return nullptr;
}
