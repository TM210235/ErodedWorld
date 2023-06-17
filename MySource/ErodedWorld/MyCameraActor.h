// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCameraActor.generated.h"

// �J�����N���X
// �C���Q�[�����̃J����
// �v���C���[�ƓG�̋����ɉ����ăA�[���̒����𒲐�����

UCLASS()
class ERODEDWORLD_API AMyCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// �R���X�g���N�^
	AMyCameraActor();

protected:
	// �X�|�[�����̏���
	virtual void BeginPlay() override;

public:	
	// ���t���[���̏���
	virtual void Tick(float DeltaTime) override;

protected:
	// �J�����̃��[�e�[�V�������x
	UPROPERTY(BlueprintReadOnly,  Category = "Const")
		float SPEED_ROTINTERP;
	// �K�E�Z�g�p���̃J�����̃��[�e�[�V�������x
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float SPEED_VMOTION_ROTINTERP;
	// �J�����A�[���̐L�k���x
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float SPEED_CAMERA;
	// �f�t�H���g�̃J�����A�[���̒���
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float DEFAULT_ARMLENGTH;
	// �ŒZ�̃J�����A�[���̒���
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MIN_ARMLENGTH;
	// �Œ��̃J�����A�[���̒���
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MAX_ARMLENGTH;
	// �K�E�Z�g�p���̃J�����̉�荞�ݒl
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float ANGLE_VMOTION_YAW;

public:
	// �K�E�Z�g�p�����ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isVMotion;
	// �J�����R���|�[�l���g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* MainCamera;
	// �J�����A�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArm;
	// �v���C���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerCharacter* player;
	// �v���C���[�̎擾����
	UFUNCTION(BlueprintCallable, Category = "Get")
		APlayerCharacter* getPlayerCharacter();
	// �v���C���[�R���g���[���[�̃��[�e�[�V�����Ƃ̓�������
	UFUNCTION(BlueprintCallable, Category = "Func")
		void LinkPlayerControlRotation(float deltaSecond);
	// �J�����A�[���̒�����������	
	UFUNCTION(BlueprintCallable, Category = "Func")
		void AdjustCameraArmLength(float deltaSecond);
	// �K�E�Z�g�p���̃J�����̏���
	UFUNCTION(BlueprintCallable, Category = "Func")
		void VMotionCameraMove(float deltaSecond);
};
