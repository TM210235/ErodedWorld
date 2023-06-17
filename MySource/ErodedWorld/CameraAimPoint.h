// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CameraAimPoint.generated.h"

// �����_�N���X
// �����_�N���X�ɑ΂��A�J�����N���X���Ǐ]���s��
// �v���C���[���̓v���C���[�ƓG�����񂾐���̓_�ɁA�����_��ݒ肷��

UCLASS()
class ERODEDWORLD_API ACameraAimPoint : public AActor
{
	GENERATED_BODY()

public:
	// �R���X�g���N�^
	ACameraAimPoint();

protected:
	// �X�|�[�����̏���
	virtual void BeginPlay() override;

public:
	// ���t���[���̏���
	virtual void Tick(float DeltaTime) override;

protected:
	// ���b�N�I�����Ă���Ώۂ̃A�N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* targetActor;
	// ���b�N�I�����Ă���Ώۂ̃A�N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		APlayerCharacter* player;
	
	// �����_�̒Ǐ]���x
	UPROPERTY(BlueprintReadOnly, Category = "Point")
		float SPEED_INTERP;

	// �v���C���[�ƃ^�[�Q�b�g�Ƃ̊Ԃ́A�ǂ̈ʒu�ɒ����_���ʒu���邩
	// 0.f(�v���C���[��) ~ 1.f(�^�[�Q�b�g��)   
	UPROPERTY(BlueprintReadOnly, Category = "Point")
		float RATIO_EASE;
};
