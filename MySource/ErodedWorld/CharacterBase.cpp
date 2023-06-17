// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemComponent.h"


// コンストラクタ
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// アビリティゲームシステム用コンポーネント
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComp"));
	AbilitySystemComp->ReplicationMode = EGameplayEffectReplicationMode::Full;
	bReplicates = true;
}
// スポーン時の処理
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// 毎フレームの処理
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Inputに処理を割り当てるためのセットアップ
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// UE4.24でGameAbillitySystemを使う際に必要な処理
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}


// PlayerState取得
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// UE4.24でGameAbillitySystemを使う際に必要な処理
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		// ゲームスタート時のAbilityを付与する処理
		AddStartupGameplayAbilities();
	}
}

// アクター情報の更新
void ACharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	// UE4.24でGameAbillitySystemを使う際に必要な処理
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->RefreshAbilityActorInfo();
	}
}

// UE4.24でGameAbillitySystemを使う際に必要な処理
void ACharacterBase::AddStartupGameplayAbilities()
{
	// AbilitySystemCompが存在するとき
	if (IsValid(AbilitySystemComp))
	{
		for (TSubclassOf<UGameplayAbility>& StartupAbility : GameplayAbilities)
		{
			// Ability を付与。TryActivateAbility などで使用できるハンドルを返す
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(StartupAbility, ExistsLevel, INDEX_NONE, this));
		}
		// 初期化フラグをオン
		bAbilitiesInitialzied = true;
	}
}