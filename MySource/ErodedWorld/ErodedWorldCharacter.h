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
	// コンストラクタ
	AErodedWorldCharacter(const FObjectInitializer& ObjectInitializer);

	// カメラの横方向の移動レート
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	// カメラの上下の角度変更の速度レート
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	// 前後の移動
	void MoveForward(float Value);

	// 左右の移動
	void MoveRight(float Value);
	// カメラの横方向の移動計算
	void TurnAtRate(float Rate);
	// カメラの上下の角度計算
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

};

