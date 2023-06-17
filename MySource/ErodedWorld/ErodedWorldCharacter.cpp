// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ErodedWorldCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// AErodedWorldCharacter���N���X
// �W�����v�͂�󒆐���ȂǁA����Ɋւ���ݒ�

AErodedWorldCharacter::AErodedWorldCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// �����蔻��T�C�Y
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// ���_�̉�]���[�g
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Pitch/Yaw/Roll������NewControlRotation�ŏ㏑�����邩�ǂ����B
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// CharacterMovement�̐ݒ�
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1600.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Input�ɏ��������蓖�Ă邽�߂̃Z�b�g�A�b�v���\�b�h
void AErodedWorldCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// �L�[�o�C���h�ݒ�------------------------------------------------------------------------
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AErodedWorldCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AErodedWorldCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AErodedWorldCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AErodedWorldCharacter::LookUpAtRate);
	// �L�[�o�C���h�ݒ�------------------------------------------------------------------------
}

// �J�����̉������̈ړ��v�Z
void AErodedWorldCharacter::TurnAtRate(float Rate)
{
	// YawInput�̌v�Z
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// �J�����̏㉺�̊p�x�v�Z
void AErodedWorldCharacter::LookUpAtRate(float Rate)
{
	// PitchInput�̌v�Z
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// ���ʂւ̈ړ�����
void AErodedWorldCharacter::MoveForward(float Value)
{
	// �ړ��\��Ԃ̏ꍇ
	if (!isAttack&&!isDamaged&&!isAction)
	{
		// �R���g���[���[�����݂��A���͒l��0�łȂ��Ƃ�
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// �O�i�̂��߂̕������擾���A�ړ��ʂ����Z����
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

// �������̈ړ�
void AErodedWorldCharacter::MoveRight(float Value)
{
	// �ړ��\��Ԃ̏ꍇ
	if (!isAttack&&!isDamaged && !isAction)
	{
		// �R���g���[���[�����݂��A���͒l��0�łȂ��Ƃ�
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// �ړ��̂��߂̕������擾���A���ړ�����
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
}
