// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCameraActor.generated.h"

// カメラクラス
// インゲーム中のカメラ
// プレイヤーと敵の距離に応じてアームの長さを調整する

UCLASS()
class ERODEDWORLD_API AMyCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// コンストラクタ
	AMyCameraActor();

protected:
	// スポーン時の処理
	virtual void BeginPlay() override;

public:	
	// 毎フレームの処理
	virtual void Tick(float DeltaTime) override;

protected:
	// カメラのローテーション速度
	UPROPERTY(BlueprintReadOnly,  Category = "Const")
		float SPEED_ROTINTERP;
	// 必殺技使用時のカメラのローテーション速度
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float SPEED_VMOTION_ROTINTERP;
	// カメラアームの伸縮速度
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float SPEED_CAMERA;
	// デフォルトのカメラアームの長さ
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float DEFAULT_ARMLENGTH;
	// 最短のカメラアームの長さ
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MIN_ARMLENGTH;
	// 最長のカメラアームの長さ
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MAX_ARMLENGTH;
	// 必殺技使用時のカメラの回り込み値
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float ANGLE_VMOTION_YAW;

public:
	// 必殺技使用中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isVMotion;
	// カメラコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* MainCamera;
	// カメラアーム
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArm;
	// プレイヤー
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerCharacter* player;
	// プレイヤーの取得処理
	UFUNCTION(BlueprintCallable, Category = "Get")
		APlayerCharacter* getPlayerCharacter();
	// プレイヤーコントローラーのローテーションとの同期処理
	UFUNCTION(BlueprintCallable, Category = "Func")
		void LinkPlayerControlRotation(float deltaSecond);
	// カメラアームの長さ調整処理	
	UFUNCTION(BlueprintCallable, Category = "Func")
		void AdjustCameraArmLength(float deltaSecond);
	// 必殺技使用時のカメラの処理
	UFUNCTION(BlueprintCallable, Category = "Func")
		void VMotionCameraMove(float deltaSecond);
};
