// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"


class UAbilitySystemComponent;
class UGameplayAbility;

// �L�����N�^�[���N���X
// GamePlayAbilities�̐ݒ������

UCLASS()
class ERODEDWORLD_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// �R���X�g���N�^
	ACharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// �X�|�[�����̏���
	virtual void BeginPlay() override;

public:	
	// ���t���[���̏���
	virtual void Tick(float DeltaTime) override;
	// Input�ɏ��������蓖�Ă邽�߂̃Z�b�g�A�b�v
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// GameAbilityComponent �L�����N�^�[�̃R���{�����A�N�V�����̂��߂Ɋ��p
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
		UAbilitySystemComponent* AbilitySystemComp;
	    UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// �U�����Ă��邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAttack;
	// �_���[�W���󂯂Ă��邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDamaged;
	// �A�N�V���������ǂ����i���̑��̍s���𐧌�����t���O�j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAction;

public:
	// 
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void OnRep_Controller() override;

// ------------------GamePlayAbilities���g�p���邽�߂ɕK�v�Ȃ���------------------
public:
	// GameplayAbility �����z��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;
public:
	// �Q�[���X�^�[�g����Ability��t�^���鏈��
	void AddStartupGameplayAbilities();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int32 ExistsLevel = 1;
	
	// GameAbilitySystem�������t���O
	UPROPERTY()
		int32 bAbilitiesInitialzied;
// ------------------GamePlayAbilities���g�p���邽�߂ɕK�v�Ȃ���------------------

};

