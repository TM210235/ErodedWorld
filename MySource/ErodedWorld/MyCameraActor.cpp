// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraActor.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// コンストラクタ
AMyCameraActor::AMyCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// コンポーネントの設定
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//-------- 定数--------
	SPEED_ROTINTERP = 6.f;						// カメラのローテーション速度
	SPEED_CAMERA = 4.f;							// カメラアームの伸縮速度
	SPEED_VMOTION_ROTINTERP = 8.f;		// 必殺技使用時のカメラのローテーション速度
	DEFAULT_ARMLENGTH = 280.f;				// デフォルトのカメラアームの長さ
	MIN_ARMLENGTH = 240.f;						// 最短のカメラアームの長さ
	MAX_ARMLENGTH = 750.f;						// 最長のカメラアームの長さ
	ANGLE_VMOTION_YAW = 120.f;				// 必殺技使用時のカメラの回り込み値
	//-------- 定数--------

	// 必殺技使用フラグ
	isVMotion = false;
}

// スポーン時の処理
void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();
	// プレイヤーを取得
	player = getPlayerCharacter();
}

// 毎フレームの処理
void AMyCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// プレイヤーが存在するとき
	if (!IsValid(player))
	{
		return;
	}
	// プレイヤーコントローラーとの同期処理
	LinkPlayerControlRotation(DeltaTime);
	// 必殺技発動中の場合
	if (isVMotion)
	{
		// 必殺技時のカメラモーション
		VMotionCameraMove(DeltaTime);
	}
	else
	{
		// カメラアームの長さ調整処理
		AdjustCameraArmLength(DeltaTime);
	}
}
// プレイヤーの取得処理
APlayerCharacter* AMyCameraActor::getPlayerCharacter()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0));
	return player;
}

// プレイヤーコントローラーのローテーションとの同期処理
void AMyCameraActor::LinkPlayerControlRotation(float deltaSecond)
{
	SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), player->GetControlRotation(), deltaSecond, SPEED_ROTINTERP));
}

// カメラアームの長さ調整処理
void AMyCameraActor::AdjustCameraArmLength(float deltaSecond)
{
	if (!IsValid(player))
	{
		return;
	}
	AActor* targetActor = player->getLockOnTarget();
	// ターゲットしている敵が存在するとき
	if (IsValid(targetActor))
	{
		// プレイヤーとターゲットの敵との距離を取得
		float armLength = UKismetMathLibrary::Vector_Distance(player->GetActorLocation(), targetActor->GetActorLocation());
			
		// ターゲットとの距離がカメラアームの上限値を超過している場合
		if (armLength > MAX_ARMLENGTH)
		{
			// 目標のカメラアームの長さを上限値に設定
			armLength = MAX_ARMLENGTH;
		}
		// ターゲットとの距離がカメラアームの下限値を下回っている場合
		else if (armLength < MIN_ARMLENGTH)
		{
			// 目標のカメラアームの長さを下限値に設定
			armLength = MIN_ARMLENGTH;
		}
		// カメラアームの長さを目標値に補正する
		SpringArm->TargetArmLength = UKismetMathLibrary::
			FInterpTo(SpringArm->TargetArmLength, armLength, deltaSecond, SPEED_CAMERA);
	}
	else 
	{
		// カメラアームの長さをデフォルト値に補正する
		SpringArm->TargetArmLength = UKismetMathLibrary::
			FInterpTo(SpringArm->TargetArmLength,DEFAULT_ARMLENGTH, deltaSecond, SPEED_CAMERA);
	}
}
// 必殺技使用時のカメラの処理
void AMyCameraActor::VMotionCameraMove(float deltaSecond)
{
	if (IsValid(player))
	{
		// プレイヤーコントローラーのRotationを目標のRotationとして取得する
		FRotator targetRot = player->GetControlRotation();
		
		// 必殺技使用時用のカメラアングルを設定する
		SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(),
			FRotator(targetRot.Pitch, targetRot.Yaw + ANGLE_VMOTION_YAW,0.f),
				deltaSecond,SPEED_VMOTION_ROTINTERP));
	}
}

	

