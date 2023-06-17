// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ErodedWorld.h"


// �R���X�g���N�^
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	//-------- �萔--------
	MAX_VPOINT = 100.0f;				// �K�E�Z���x���̍ő�l
	RATE_COMBO_RAR = 20.0f;		// �R���{�� / RATE_COMBO_RAR ���U���͂̔{���ɂȂ�
	RATE_SPATTACK = 1.5f;				// ����U���̍U���{��
	RATE_VATTACK = 3.0f;				// �K�E�Z�̍U���{��
	POWER_KNOCKBACK = -20.0f;	// �m�b�N�o�b�N���ɐ�����ԈЗ�
	RANGE_DASHATTACK = 300.0f;	// �ʏ�U�����_�b�V���U���ɕω����鋗��
	TIME_COMBO = 120;					// �R���{�p������
	TIME_INVINCIBLE = 42;				// ���G����
	TIME_KNOCKBACK = 60;			// �m�b�N�o�b�N����
	MAX_VLEVEL = 3;						// �K�E�Z���x���̏��
	TIME_SPOINT_HEAL = 300;		// �X�L���|�C���g�������񕜂��n�߂鎞��
	LOST_VPOINT = 0.05f;				// 1f���Ɍ�������K�E�Z�Q�[�W�̗�
	ADD_VPOINT = 5.0f;					// �U�����q�b�g���閈�ɉ񕜂������Q�[�W�̗�
	BASE_ATTACK = 2.5f;				// ��b�U����
	//-------- �萔--------

	// �A�j���[�V�����ɂ��ړ����������ǂ���
	isAnimMove = false;
	// ���m�͈͓��̓G�ɏƏ����ݒ肳��Ă��邩�ǂ���
	isLockOn = false;
	// ��𒆂��ǂ���
	isDodge = false;
	// ��b�ł����Ԃ��ǂ���
	canTalk = false;
	// �K�E�Z���x�����ő傩�ǂ����B�ő厞�͕K�E�Z�Q�[�W�����Ԍo�߂Ō������Ȃ�
	isVLevelMax = false;
	// �m�b�N�o�b�N�����ǂ���
	isKnockBack = false;
	// ���S���Ă��邩�ǂ���
	isDead = false;
	// �R���{�����ǂ���
	isCombo = false;
	// �L�����Z���s��Ԃ��ǂ���
	cantCancel = false;
	// �A�N�V�����{�^���A�ł�h���t���O
	isActionBlock = false;
	// �v�O��ǂ݂Ƃ��Ă����Ԃ��ǂ���
	isReport = false;
	// �K�C�h���b�Z�[�W�\�������ǂ���
	isGuide = false;
	// ���݂̃R���{���[�g
	comboRate = 0.f;
	// ���݂̃m�b�N�o�b�N���x
	knockBackPower = 0.f;
	// ���݂̃A�j���[�V�����Đ�����
	animTimer = 0.f;
	// �R���{�^�C�}�[
	comboTimer = TIME_COMBO;
	// ����U���Q�[�W�񕜂̃^�C�}�[
	autoHealSpTimer = 0;
	// ���݂̕K�E�Z���x��
	currentVLevel = 1;
	// ���݂̃R���{��
	comboCnt = 0;
	// ���G���ԃ^�C�}�[
	invincibleTimer = 0;
	// �m�b�N�o�b�N�^�C�}�[
	knockBackTimer = 0;
	// ���b�N�I���^�[�Q�b�g�p�̕ϐ�
	lockOnTarget = NULL;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InvincibleTimer();
	KnockBack(DeltaTime);
	LostVPoint();
}
// �U���\��Ԃ���Ԃ�
bool APlayerCharacter::Can_Attack()
{
	// �U���\��Ԃ���Ԃ�
	return (!isAction && !isKnockBack && !cantCancel && !isDodge);
}
// �K�E�Z�\��Ԃ���Ԃ�
bool APlayerCharacter::Can_VAttack()
{
	// �K�E�Z�\��Ԃ���Ԃ�
	return (!isAction && !isKnockBack && !isDodge);
}

// �A�N�V�����\��Ԃ���Ԃ�
bool APlayerCharacter::Can_Action()
{
	// �A�N�V�����\��Ԃ���Ԃ�
	return (canTalk && !isKnockBack && !isAttack && !isActionBlock);
}


// �R���{�p�����Ԓ����ǂ�����Ԃ�
bool APlayerCharacter::is_ComboKeep()
{
	// �R���{�p�����Ԃ����炷
	--comboTimer;
	// �R���{�p�����Ԓ����ǂ���
	if (comboTimer <= 0)
	{
		// �R���{�̃��Z�b�g����
		comboCnt = 0;
		isCombo = false;
	}
	return isCombo;
}

// �A�N�V������Ԃ�؂�ւ���
void APlayerCharacter::SwitchAction()
{
	// �A�N�V������Ԃ�؂�ւ���
	isAction = !isAction;
	// �A�N�V�������͖��G��Ԃɂ���
	isDodge = isAction;
}

void APlayerCharacter::AttackOff()
{
	// �U���Ɋւ���t���O��������
	isAttack = false;
	cantCancel = false;
}

// ���Ԍo�߂ɂ��K�E�Z�Q�[�W�����炷����
void APlayerCharacter::LostVPoint()
{
	// �K�E�Z�Q�[�W���ő�łȂ�����0�łȂ��Ƃ�
	if (!isVLevelMax && vPoint > 0.f)
	{
		// �K�E�Z�Q�[�W�����炷
		vPoint -= LOST_VPOINT;
	}
}
void APlayerCharacter::AddVPoint()
{
	// �K�E�Z�Q�[�W�𑝉�����
	vPoint += ADD_VPOINT;
	
	// �K�E�Z�Q�[�W������𒴂�����

	if (vPoint > MAX_VPOINT)
	{	
		// �K�E�Z���x�����J��グ��
		vPoint -= MAX_VPOINT;
		++currentVLevel;
		
		// �K�E�Z���x�����ő�l�ɂȂ����Ƃ�
		if (currentVLevel >= MAX_VLEVEL)
		{
			// �K�E�Z���x���ő�̃t���O�𗧂Ă�
			isVLevelMax = true;
			
			// �K�E�Z�Q�[�W�A���x����␳����
			vPoint = MAX_VPOINT;
			currentVLevel = MAX_VLEVEL;
		}
	}
}

// UI�X�V�p
float APlayerCharacter::GetVPointPerMaxVPoint()
{
	// �K�E�Z�Q�[�W�̊�����Ԃ�
	return vPoint / MAX_VPOINT;
}

// �R���{�̃J�E���g���� 
float APlayerCharacter::ComboCntUp()
{
	// �R���{���𑝉�������
	++comboCnt;

	// �R���{�p�����Ԃ����Z�b�g����
	comboTimer = TIME_COMBO;
	
	// �R���{���ɉ������U���{����ݒ肷��i2�R���{�ڂ���{����������̂� �R���{������1�������j 
	comboRate = (float)(comboCnt - 1) / RATE_COMBO_RAR + 1.f;
	
	// �R���{����Ԃ�
	return comboCnt;
}

// �m�b�N�o�b�N�̏���
void APlayerCharacter::KnockBack(float deltaseconds)
{
	// �m�b�N�o�b�N��
	if (isKnockBack)
	{
		// �v���C���[������ɔ�΂�
		knockBackPower += deltaseconds;
		float x = UKismetMathLibrary::Ease(POWER_KNOCKBACK, 0.f, knockBackPower, EEasingFunc::ExpoOut);
		AddActorLocalOffset(FVector(x, 0.f, 0.f), true);
		KnockBackTimer();
	}
}

// ���b�N�I�����m���ɂ���ŋߋ����̓G���擾����
AActor* APlayerCharacter::getNearActor(const TArray<AActor*>& actors)
{
	// ���b�N�I�����m���ɂ���A�N�^�[�����擾���� 
	int length = actors.Num();
	if (length != 0)
	{
		// �z��̐擪���ŋߋ����Ɖ��肷��
		AActor* nearActor = actors[0];

		for (int i = 1; i < length; i++)
		{
			if (!IsValid(actors[i]))
			{
				continue;
			}
			// ���v���C���[�ɋ߂��A�N�^�[��nearActor�ɑ������
			if (nearActor->GetHorizontalDistanceTo(this) > actors[i]->GetHorizontalDistanceTo(this))
			{
				nearActor = actors[i];
			}
		}
		// �ŋߋ����̓G��Ԃ�
		return nearActor;
	}
	else 
	{
		// �t�߂ɓG�����Ȃ��ꍇ
		return NULL;
	}
}
//  lockOnTarget�̃Q�b�^�[
AActor* APlayerCharacter::getLockOnTarget() const
{
	return lockOnTarget;
}


// �m�b�N�o�b�N�̃^�C�}�[����
void APlayerCharacter::KnockBackTimer()
{
	// �m�b�N�o�b�N�p�����ԓ��̏ꍇ
	if (knockBackTimer < TIME_KNOCKBACK)
	{
		// �^�C�}�[���J�E���g����
		knockBackTimer++;
	}
	else
	{
		// �m�b�N�o�b�N�������I����
		knockBackTimer = 0;
		isKnockBack = false;
	}
}
// ��_���[�W����
// �_���[�W�������s�����ǂ�����Ԃ�
bool APlayerCharacter::Check_Damaged(AActor* damageHost)
{
	// �_���[�W��̖��G���ԊO����𒆂łȂ��ꍇ�_���[�W�������s��
	if (isDamaged || isDodge)
	{
		return false;
	}
	// �U���t���O���I�t�ɂ���
	AttackOff();
	knockBackPower = 0;
	
	// �_���[�W�n�t���O���I���ɂ���
	isDamaged = true;
	isKnockBack = true;

	if (IsValid(damageHost))
	{
		// �U����^���Ă�������̕�������
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FVector(GetActorLocation()), FVector(damageHost->GetActorLocation())));
	}
	return true;
}
// ���G���Ԃ̏���
void APlayerCharacter::InvincibleTimer()
{
	// �_���[�W���󂯂Ă���ꍇ�������s��
	if (!isDamaged)
	{
		return ;
	}
	// �^�C�}�[���J�E���g�A�b�v
	if (invincibleTimer < TIME_INVINCIBLE)
	{
		invincibleTimer++;
	}
	// �^�C�}�[�����G���Ԃ𒴉߂����ꍇ
	else
	{
		// Damage�t���O�ƃ^�C�}�[�����Z�b�g����
		isDamaged = false;
		invincibleTimer = 0;
	}
}

