// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ErodedWorldCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// AErodedWorldCharacter基底クラス
// ジャンプ力や空中制御など、操作に関する設定

AErodedWorldCharacter::AErodedWorldCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// 当たり判定サイズ
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 視点の回転レート
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Pitch/Yaw/Rollを引数NewControlRotationで上書きするかどうか。
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// CharacterMovementの設定
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1600.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Inputに処理を割り当てるためのセットアップメソッド
void AErodedWorldCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// キーバインド設定------------------------------------------------------------------------
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AErodedWorldCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AErodedWorldCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AErodedWorldCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AErodedWorldCharacter::LookUpAtRate);
	// キーバインド設定------------------------------------------------------------------------
}

// カメラの横方向の移動計算
void AErodedWorldCharacter::TurnAtRate(float Rate)
{
	// YawInputの計算
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// カメラの上下の角度計算
void AErodedWorldCharacter::LookUpAtRate(float Rate)
{
	// PitchInputの計算
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// 正面への移動処理
void AErodedWorldCharacter::MoveForward(float Value)
{
	// 移動可能状態の場合
	if (!isAttack&&!isDamaged&&!isAction)
	{
		// コントローラーが存在し、入力値が0でないとき
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// 前進のための方向を取得し、移動量を加算する
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

// 横方向の移動
void AErodedWorldCharacter::MoveRight(float Value)
{
	// 移動可能状態の場合
	if (!isAttack&&!isDamaged && !isAction)
	{
		// コントローラーが存在し、入力値が0でないとき
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// 移動のための方向を取得し、横移動する
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
}
