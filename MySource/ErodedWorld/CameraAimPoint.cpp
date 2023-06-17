// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraAimPoint.h"

// 注視点クラス
// 注視点クラスに対し、カメラクラスが追従を行う
// プレイヤー又はプレイヤーと敵を結んだ線上の点に、注視点を設定する

// コンストラクタ
ACameraAimPoint::ACameraAimPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	SPEED_INTERP = 6.f;			// 注視点の速度
	RATIO_EASE = 0.3f;			// 敵をターゲットしている時の、注視点の補間位置
}

// スポーン時の処理
void ACameraAimPoint::BeginPlay()
{
	Super::BeginPlay();
	// プレイヤーを取得
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0));
}

// 毎フレームの処理
void ACameraAimPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// プレイヤーが存在するとき処理を行う
	if (!IsValid(player))
	{
		return;
	}
	FVector targetLocation;
	// プレイヤーがターゲットしている敵がいる場合
	if (player->getLockOnTarget())
	{
		// ターゲットしている敵を取得
		targetActor = Cast<AActor>(player->getLockOnTarget());
		// ターゲットしている敵とプレイヤーの位置の中間あたりを取得する
		targetLocation = UKismetMathLibrary::VEase(FVector(player->GetActorLocation()), FVector(targetActor->GetActorLocation()), RATIO_EASE, EEasingFunc::Linear);
	}
	else
	{
		// プレイヤーの位置を取得する
		targetLocation = player->GetActorLocation();
	}
	// 注視点の目標値を設定
	// 注視点を補正しながら目標値に合わせる
	FVector location = UKismetMathLibrary::VInterpTo(GetActorLocation(), targetLocation, DeltaTime, SPEED_INTERP);
	// 注視点の移動
	SetActorLocation(location);
}


