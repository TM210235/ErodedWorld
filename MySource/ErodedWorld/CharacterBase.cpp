// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemComponent.h"


// �R���X�g���N�^
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// �A�r���e�B�Q�[���V�X�e���p�R���|�[�l���g
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComp"));
	AbilitySystemComp->ReplicationMode = EGameplayEffectReplicationMode::Full;
	bReplicates = true;
}
// �X�|�[�����̏���
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// ���t���[���̏���
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Input�ɏ��������蓖�Ă邽�߂̃Z�b�g�A�b�v
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// UE4.24��GameAbillitySystem���g���ۂɕK�v�ȏ���
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}


// PlayerState�擾
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// UE4.24��GameAbillitySystem���g���ۂɕK�v�ȏ���
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		// �Q�[���X�^�[�g����Ability��t�^���鏈��
		AddStartupGameplayAbilities();
	}
}

// �A�N�^�[���̍X�V
void ACharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	// UE4.24��GameAbillitySystem���g���ۂɕK�v�ȏ���
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->RefreshAbilityActorInfo();
	}
}

// UE4.24��GameAbillitySystem���g���ۂɕK�v�ȏ���
void ACharacterBase::AddStartupGameplayAbilities()
{
	// AbilitySystemComp�����݂���Ƃ�
	if (IsValid(AbilitySystemComp))
	{
		for (TSubclassOf<UGameplayAbility>& StartupAbility : GameplayAbilities)
		{
			// Ability ��t�^�BTryActivateAbility �ȂǂŎg�p�ł���n���h����Ԃ�
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(StartupAbility, ExistsLevel, INDEX_NONE, this));
		}
		// �������t���O���I��
		bAbilitiesInitialzied = true;
	}
}