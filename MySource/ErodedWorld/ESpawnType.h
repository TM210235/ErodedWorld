// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ESpawnType.generated.h"
/**
 * Player�̃X�|�[���ʒu�����߂�
 * 
 */
UENUM(BlueprintType)
enum class ESpawnType: uint8
{
	Tutorial,			// �`���[�g���A���X�e�[�W
	AdvStart,		// �A�h�x���`���[�}�b�v���X�^�[�g�n�_
	AdvDrHouse,	// �A�h�x���`���[�}�b�v�����m�̌������O
	AdvGate,		// �A�h�x���`���[�}�b�v���{�X���̑O
	BossMap,		// �{�X�}�b�v
};