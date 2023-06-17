// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ErodedWorldCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.generated.h"

 
// �v���C���[�L�����N�^�[�N���X

UCLASS()
class ERODEDWORLD_API APlayerCharacter : public AErodedWorldCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
public:
	virtual void Tick(float DeltaTime) override;


protected:
	// �K�E�Z�Q�[�W�̍ő�l
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MAX_VPOINT;
	
	// ��b�U����
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float BASE_ATTACK;
	
	// �R���{���̍U���{�� �@�R���{�� / COMBO_RAR_RATE
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_COMBO_RAR;

	// ����U���̍U���{��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_SPATTACK;
	// �K�E�Z�̍U���{��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_VATTACK;
	// �m�b�N�o�b�N�̗�
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float POWER_KNOCKBACK;
	// �_�b�V���A�^�b�N���������鋗��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RANGE_DASHATTACK;
	// ���Ԍo�߂Ō�������K�E�Z�|�C���g�̒l
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float LOST_VPOINT;
	// 1�q�b�g���Ƃɉ��Z�����K�E�Z�|�C���g�̒l
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float ADD_VPOINT;
	// �R���{���p������t���[��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_COMBO;
	// �X�L���|�C���g�������񕜂���܂ł̎���
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_SPOINT_HEAL;
	// �K�E�Z���x���̏��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int MAX_VLEVEL;
	// �m�b�N�o�b�N���Ă��鎞��
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_KNOCKBACK;
	// �U�����󂯂���̖��G����
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_INVINCIBLE;

public:
	// �A�j���[�V�����ɂ��ړ������ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAnimMove;
	
	// ���m�͈͓��̓G�ɏƏ����ݒ肳��Ă��邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isLockOn;
	
	// ��𒆂��ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDodge;
	
	// ��b�����ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool canTalk;
	// �K�E�Z���x�����ő傩�ǂ����B�ő厞�͕K�E�Z�Q�[�W�����Ԍo�߂Ō������Ȃ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isVLevelMax;
	
	// �m�b�N�o�b�N�����ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isKnockBack;
	// ���S���Ă��邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDead;
	// �R���{�����ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isCombo;
	// �U���̃L�����Z�����󂯕t���邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool cantCancel;
	// �A�N�V�����{�^���̘A�Ŗh�~�t���O
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isActionBlock;
	// �v�O��A�C�e���̃��b�Z�[�W��\�������ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isReport;
	// �{�^���K�C�h��\�������ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isGuide;
	// ���݂̃m�b�N�o�b�N�l
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float knockBackPower;
	// �R���{�ɂ��U���{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float comboRate;
	// �A�j���[�V�����̃^�C�}�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		float animTimer;
	// �K�E�Z�Q�[�W
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float vPoint;
	// �R���{�p���p�̃^�C�}�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int comboTimer;
	// ����Q�[�W�����񕜗p�̃^�C�}�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int autoHealSpTimer;
	// ���݂̕K�E�Z���x��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int currentVLevel;
	// �R���{�J�E���g�p�ϐ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int comboCnt;
	// ���G���ԗp�^�C�}�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int invincibleTimer;
	// �m�b�N�o�b�N�p�^�C�}�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int knockBackTimer;
	// ���b�N�I���^�[�Q�b�g�p�̕ϐ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* lockOnTarget;


	// �U���\��Ԃ��ǂ�����Ԃ�
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_Attack();
	// �K�E�Z�\��Ԃ��ǂ�����Ԃ�
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_VAttack();
	// �A�N�V�����\��Ԃ��ǂ�����Ԃ�
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_Action();
	// �R���{�p������𒲂ׂ�
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool is_ComboKeep();
	// �A�N�V�����t���O��؂�ւ���
	UFUNCTION(BlueprintCallable, Category = "Func")
		void SwitchAction();
	// �U���t���O��؂�
	UFUNCTION(BlueprintCallable, Category = "Func")
		void AttackOff();
	// ���Ԍo�߂Ō�������K�E�Z�Q�[�W�̏���
	UFUNCTION(BlueprintCallable, Category = "Lost")
		void LostVPoint();
	// �K�E�Z�Q�[�W�̑�������
	UFUNCTION(BlueprintCallable, Category = "Add")
		void AddVPoint();
	// UI�X�V�p �K�E�Z�Q�[�W�̊���
	UFUNCTION(BlueprintCallable, Category = "Get")
		float GetVPointPerMaxVPoint();
	// �m�b�N�o�b�N����
	UFUNCTION(BlueprintCallable, Category = "Func")
		void KnockBack(float deltaseconds);
	
	// �R���{�̃J�E���g�A�b�v����
	UFUNCTION(BlueprintCallable, Category = "Count")
		float ComboCntUp();
	
	// �m�b�N�o�b�N�̎��Ԍv������
	UFUNCTION(BlueprintCallable, Category = "Timer")
		void KnockBackTimer();
	
	// �_���[�W�������s�������ǂ������擾
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Check_Damaged(AActor* damageHost);
	
	void InvincibleTimer();
	
	// ��ԋ߂��ɂ���G���擾����
	UFUNCTION(BlueprintCallable, Category = "Get")
		AActor* getNearActor(const TArray<AActor*>& actors);

	// lockOnTarget�̃Q�b�^�[
	AActor* getLockOnTarget() const;
};
