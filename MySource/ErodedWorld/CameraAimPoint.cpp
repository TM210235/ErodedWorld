// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraAimPoint.h"

// �����_�N���X
// �����_�N���X�ɑ΂��A�J�����N���X���Ǐ]���s��
// �v���C���[���̓v���C���[�ƓG�����񂾐���̓_�ɁA�����_��ݒ肷��

// �R���X�g���N�^
ACameraAimPoint::ACameraAimPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	SPEED_INTERP = 6.f;			// �����_�̑��x
	RATIO_EASE = 0.3f;			// �G���^�[�Q�b�g���Ă��鎞�́A�����_�̕�Ԉʒu
}

// �X�|�[�����̏���
void ACameraAimPoint::BeginPlay()
{
	Super::BeginPlay();
	// �v���C���[���擾
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0));
}

// ���t���[���̏���
void ACameraAimPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �v���C���[�����݂���Ƃ��������s��
	if (!IsValid(player))
	{
		return;
	}
	FVector targetLocation;
	// �v���C���[���^�[�Q�b�g���Ă���G������ꍇ
	if (player->getLockOnTarget())
	{
		// �^�[�Q�b�g���Ă���G���擾
		targetActor = Cast<AActor>(player->getLockOnTarget());
		// �^�[�Q�b�g���Ă���G�ƃv���C���[�̈ʒu�̒��Ԃ�������擾����
		targetLocation = UKismetMathLibrary::VEase(FVector(player->GetActorLocation()), FVector(targetActor->GetActorLocation()), RATIO_EASE, EEasingFunc::Linear);
	}
	else
	{
		// �v���C���[�̈ʒu���擾����
		targetLocation = player->GetActorLocation();
	}
	// �����_�̖ڕW�l��ݒ�
	// �����_��␳���Ȃ���ڕW�l�ɍ��킹��
	FVector location = UKismetMathLibrary::VInterpTo(GetActorLocation(), targetLocation, DeltaTime, SPEED_INTERP);
	// �����_�̈ړ�
	SetActorLocation(location);
}


