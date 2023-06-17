// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "ErodedWorldCharacter.generated.h"

UCLASS(config=Game)
class AErodedWorldCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	// �R���X�g���N�^
	AErodedWorldCharacter(const FObjectInitializer& ObjectInitializer);

	// �J�����̉������̈ړ����[�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	// �J�����̏㉺�̊p�x�ύX�̑��x���[�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	// �O��̈ړ�
	void MoveForward(float Value);

	// ���E�̈ړ�
	void MoveRight(float Value);
	// �J�����̉������̈ړ��v�Z
	void TurnAtRate(float Rate);
	// �J�����̏㉺�̊p�x�v�Z
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

};

