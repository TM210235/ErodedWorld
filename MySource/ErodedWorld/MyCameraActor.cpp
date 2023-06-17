// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraActor.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// �R���X�g���N�^
AMyCameraActor::AMyCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// �R���|�[�l���g�̐ݒ�
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//-------- �萔--------
	SPEED_ROTINTERP = 6.f;						// �J�����̃��[�e�[�V�������x
	SPEED_CAMERA = 4.f;							// �J�����A�[���̐L�k���x
	SPEED_VMOTION_ROTINTERP = 8.f;		// �K�E�Z�g�p���̃J�����̃��[�e�[�V�������x
	DEFAULT_ARMLENGTH = 280.f;				// �f�t�H���g�̃J�����A�[���̒���
	MIN_ARMLENGTH = 240.f;						// �ŒZ�̃J�����A�[���̒���
	MAX_ARMLENGTH = 750.f;						// �Œ��̃J�����A�[���̒���
	ANGLE_VMOTION_YAW = 120.f;				// �K�E�Z�g�p���̃J�����̉�荞�ݒl
	//-------- �萔--------

	// �K�E�Z�g�p�t���O
	isVMotion = false;
}

// �X�|�[�����̏���
void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();
	// �v���C���[���擾
	player = getPlayerCharacter();
}

// ���t���[���̏���
void AMyCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �v���C���[�����݂���Ƃ�
	if (!IsValid(player))
	{
		return;
	}
	// �v���C���[�R���g���[���[�Ƃ̓�������
	LinkPlayerControlRotation(DeltaTime);
	// �K�E�Z�������̏ꍇ
	if (isVMotion)
	{
		// �K�E�Z���̃J�������[�V����
		VMotionCameraMove(DeltaTime);
	}
	else
	{
		// �J�����A�[���̒�����������
		AdjustCameraArmLength(DeltaTime);
	}
}
// �v���C���[�̎擾����
APlayerCharacter* AMyCameraActor::getPlayerCharacter()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0));
	return player;
}

// �v���C���[�R���g���[���[�̃��[�e�[�V�����Ƃ̓�������
void AMyCameraActor::LinkPlayerControlRotation(float deltaSecond)
{
	SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), player->GetControlRotation(), deltaSecond, SPEED_ROTINTERP));
}

// �J�����A�[���̒�����������
void AMyCameraActor::AdjustCameraArmLength(float deltaSecond)
{
	if (!IsValid(player))
	{
		return;
	}
	AActor* targetActor = player->getLockOnTarget();
	// �^�[�Q�b�g���Ă���G�����݂���Ƃ�
	if (IsValid(targetActor))
	{
		// �v���C���[�ƃ^�[�Q�b�g�̓G�Ƃ̋������擾
		float armLength = UKismetMathLibrary::Vector_Distance(player->GetActorLocation(), targetActor->GetActorLocation());
			
		// �^�[�Q�b�g�Ƃ̋������J�����A�[���̏���l�𒴉߂��Ă���ꍇ
		if (armLength > MAX_ARMLENGTH)
		{
			// �ڕW�̃J�����A�[���̒���������l�ɐݒ�
			armLength = MAX_ARMLENGTH;
		}
		// �^�[�Q�b�g�Ƃ̋������J�����A�[���̉����l��������Ă���ꍇ
		else if (armLength < MIN_ARMLENGTH)
		{
			// �ڕW�̃J�����A�[���̒����������l�ɐݒ�
			armLength = MIN_ARMLENGTH;
		}
		// �J�����A�[���̒�����ڕW�l�ɕ␳����
		SpringArm->TargetArmLength = UKismetMathLibrary::
			FInterpTo(SpringArm->TargetArmLength, armLength, deltaSecond, SPEED_CAMERA);
	}
	else 
	{
		// �J�����A�[���̒������f�t�H���g�l�ɕ␳����
		SpringArm->TargetArmLength = UKismetMathLibrary::
			FInterpTo(SpringArm->TargetArmLength,DEFAULT_ARMLENGTH, deltaSecond, SPEED_CAMERA);
	}
}
// �K�E�Z�g�p���̃J�����̏���
void AMyCameraActor::VMotionCameraMove(float deltaSecond)
{
	if (IsValid(player))
	{
		// �v���C���[�R���g���[���[��Rotation��ڕW��Rotation�Ƃ��Ď擾����
		FRotator targetRot = player->GetControlRotation();
		
		// �K�E�Z�g�p���p�̃J�����A���O����ݒ肷��
		SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(),
			FRotator(targetRot.Pitch, targetRot.Yaw + ANGLE_VMOTION_YAW,0.f),
				deltaSecond,SPEED_VMOTION_ROTINTERP));
	}
}

	

