// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyrimPawnExtensionComponent.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Skyrim/SkyrimGameplayTags.h"

const FName USkyrimPawnExtensionComponent::NAME_ActorFeatureName("PawnExtenstion");

USkyrimPawnExtensionComponent::USkyrimPawnExtensionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

/* 컴포넌트가 액터에 등록(Attach)될 때 호출됨 */
void USkyrimPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	// 폰 생성 확인
	const APawn* Pawn = GetPawn<APawn>();
	ensureAlwaysMsgf((Pawn != nullptr), TEXT("SkyrimPawnExtensionComponent on [%s] can only be added to Pawn actors."), *GetNameSafe(GetOwner()));

	// GameFrameWork에 컴포넌트 등록
	RegisterInitStateFeature();
}

void USkyrimPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// 다른 컴포넌트들의 상태 변화 감지 등록 (상태 변경시 
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);
	
	// 컴포넌트 상태 변화 시도
	ensure(TryToChangeInitState(SkyrimGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void USkyrimPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// GameFrameWork에 컴포넌트 등록 해제
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

bool USkyrimPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	
	if (!CurrentState.IsValid() && DesiredState == SkyrimGameplayTags::InitState_Spawned)
	{
		// Pawn에 부착되었는지 확인
		if (Pawn)
		{
			return true;
		}
	}
	
	if (CurrentState == SkyrimGameplayTags::InitState_Spawned && DesiredState == SkyrimGameplayTags::InitState_DataAvailable)
	{
		// Pawn data is required.
		/*if (!PawnData)
		{
			return false;
		}
		*/
		
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		if (bIsLocallyControlled)
		{
			// 컨트롤러에 의해 빙의된 상태인지 확인
			if (!GetController<AController>())
			{
				return false;
			}
		}

		return true;
	}
	else if (CurrentState == SkyrimGameplayTags::InitState_DataAvailable && DesiredState == SkyrimGameplayTags::InitState_DataInitialized)
	{
		// Transition to initialize if all features have their data available
		return Manager->HaveAllFeaturesReachedInitState(Pawn, SkyrimGameplayTags::InitState_DataAvailable);
	}
	else if (CurrentState == SkyrimGameplayTags::InitState_DataInitialized && DesiredState == SkyrimGameplayTags::InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

// 다른 컴포넌트의 상태 변경이 감지된 경우 호출됨
void USkyrimPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		if (Params.FeatureState == SkyrimGameplayTags::InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

// 다른 컴포넌트들의 상태와 자신의 상태를 강제로 업데이트하는 함수
void USkyrimPawnExtensionComponent::CheckDefaultInitialization()
{
	CheckDefaultInitializationForImplementers();

	static const TArray<FGameplayTag> StateChain = { SkyrimGameplayTags::InitState_Spawned, SkyrimGameplayTags::InitState_DataAvailable, SkyrimGameplayTags::InitState_DataInitialized, SkyrimGameplayTags::InitState_GameplayReady };

	ContinueInitStateChain(StateChain);
}


