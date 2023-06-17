// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CameraAimPoint.generated.h"

// 注視点クラス
// 注視点クラスに対し、カメラクラスが追従を行う
// プレイヤー又はプレイヤーと敵を結んだ線上の点に、注視点を設定する

UCLASS()
class ERODEDWORLD_API ACameraAimPoint : public AActor
{
	GENERATED_BODY()

public:
	// コンストラクタ
	ACameraAimPoint();

protected:
	// スポーン時の処理
	virtual void BeginPlay() override;

public:
	// 毎フレームの処理
	virtual void Tick(float DeltaTime) override;

protected:
	// ロックオンしている対象のアクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* targetActor;
	// ロックオンしている対象のアクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		APlayerCharacter* player;
	
	// 注視点の追従速度
	UPROPERTY(BlueprintReadOnly, Category = "Point")
		float SPEED_INTERP;

	// プレイヤーとターゲットとの間の、どの位置に注視点を位置するか
	// 0.f(プレイヤー側) ~ 1.f(ターゲット側)   
	UPROPERTY(BlueprintReadOnly, Category = "Point")
		float RATIO_EASE;
};
