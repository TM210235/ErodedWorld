// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ErodedWorld.h"


// コンストラクタ
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	//-------- 定数--------
	MAX_VPOINT = 100.0f;				// 必殺技レベルの最大値
	RATE_COMBO_RAR = 20.0f;		// コンボ数 / RATE_COMBO_RAR が攻撃力の倍率になる
	RATE_SPATTACK = 1.5f;				// 特殊攻撃の攻撃倍率
	RATE_VATTACK = 3.0f;				// 必殺技の攻撃倍率
	POWER_KNOCKBACK = -20.0f;	// ノックバック時に吹っ飛ぶ威力
	RANGE_DASHATTACK = 300.0f;	// 通常攻撃がダッシュ攻撃に変化する距離
	TIME_COMBO = 120;					// コンボ継続時間
	TIME_INVINCIBLE = 42;				// 無敵時間
	TIME_KNOCKBACK = 60;			// ノックバック時間
	MAX_VLEVEL = 3;						// 必殺技レベルの上限
	TIME_SPOINT_HEAL = 300;		// スキルポイントが自動回復を始める時間
	LOST_VPOINT = 0.05f;				// 1f毎に減少する必殺技ゲージの量
	ADD_VPOINT = 5.0f;					// 攻撃がヒットする毎に回復する特殊ゲージの量
	BASE_ATTACK = 2.5f;				// 基礎攻撃力
	//-------- 定数--------

	// アニメーションによる移動処理中かどうか
	isAnimMove = false;
	// 検知範囲内の敵に照準が設定されているかどうか
	isLockOn = false;
	// 回避中かどうか
	isDodge = false;
	// 会話できる状態かどうか
	canTalk = false;
	// 必殺技レベルが最大かどうか。最大時は必殺技ゲージが時間経過で減少しない
	isVLevelMax = false;
	// ノックバック中かどうか
	isKnockBack = false;
	// 死亡しているかどうか
	isDead = false;
	// コンボ中かどうか
	isCombo = false;
	// キャンセル不可状態かどうか
	cantCancel = false;
	// アクションボタン連打を防ぐフラグ
	isActionBlock = false;
	// 思念を読みとっている状態かどうか
	isReport = false;
	// ガイドメッセージ表示中かどうか
	isGuide = false;
	// 現在のコンボレート
	comboRate = 0.f;
	// 現在のノックバック速度
	knockBackPower = 0.f;
	// 現在のアニメーション再生時間
	animTimer = 0.f;
	// コンボタイマー
	comboTimer = TIME_COMBO;
	// 特殊攻撃ゲージ回復のタイマー
	autoHealSpTimer = 0;
	// 現在の必殺技レベル
	currentVLevel = 1;
	// 現在のコンボ数
	comboCnt = 0;
	// 無敵時間タイマー
	invincibleTimer = 0;
	// ノックバックタイマー
	knockBackTimer = 0;
	// ロックオンターゲット用の変数
	lockOnTarget = NULL;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InvincibleTimer();
	KnockBack(DeltaTime);
	LostVPoint();
}
// 攻撃可能状態かを返す
bool APlayerCharacter::Can_Attack()
{
	// 攻撃可能状態かを返す
	return (!isAction && !isKnockBack && !cantCancel && !isDodge);
}
// 必殺技可能状態かを返す
bool APlayerCharacter::Can_VAttack()
{
	// 必殺技可能状態かを返す
	return (!isAction && !isKnockBack && !isDodge);
}

// アクション可能状態かを返す
bool APlayerCharacter::Can_Action()
{
	// アクション可能状態かを返す
	return (canTalk && !isKnockBack && !isAttack && !isActionBlock);
}


// コンボ継続時間中かどうかを返す
bool APlayerCharacter::is_ComboKeep()
{
	// コンボ継続時間を減らす
	--comboTimer;
	// コンボ継続時間中かどうか
	if (comboTimer <= 0)
	{
		// コンボのリセット処理
		comboCnt = 0;
		isCombo = false;
	}
	return isCombo;
}

// アクション状態を切り替える
void APlayerCharacter::SwitchAction()
{
	// アクション状態を切り替える
	isAction = !isAction;
	// アクション中は無敵状態にする
	isDodge = isAction;
}

void APlayerCharacter::AttackOff()
{
	// 攻撃に関するフラグを下げる
	isAttack = false;
	cantCancel = false;
}

// 時間経過による必殺技ゲージを減らす処理
void APlayerCharacter::LostVPoint()
{
	// 必殺技ゲージが最大でないかつ0でないとき
	if (!isVLevelMax && vPoint > 0.f)
	{
		// 必殺技ゲージを減らす
		vPoint -= LOST_VPOINT;
	}
}
void APlayerCharacter::AddVPoint()
{
	// 必殺技ゲージを増加する
	vPoint += ADD_VPOINT;
	
	// 必殺技ゲージが上限を超えた時

	if (vPoint > MAX_VPOINT)
	{	
		// 必殺技レベルを繰り上げる
		vPoint -= MAX_VPOINT;
		++currentVLevel;
		
		// 必殺技レベルが最大値になったとき
		if (currentVLevel >= MAX_VLEVEL)
		{
			// 必殺技レベル最大のフラグを立てる
			isVLevelMax = true;
			
			// 必殺技ゲージ、レベルを補正する
			vPoint = MAX_VPOINT;
			currentVLevel = MAX_VLEVEL;
		}
	}
}

// UI更新用
float APlayerCharacter::GetVPointPerMaxVPoint()
{
	// 必殺技ゲージの割合を返す
	return vPoint / MAX_VPOINT;
}

// コンボのカウント処理 
float APlayerCharacter::ComboCntUp()
{
	// コンボ数を増加させる
	++comboCnt;

	// コンボ継続時間をリセットする
	comboTimer = TIME_COMBO;
	
	// コンボ数に応じた攻撃倍率を設定する（2コンボ目から倍率がかかるので コンボ数から1を引く） 
	comboRate = (float)(comboCnt - 1) / RATE_COMBO_RAR + 1.f;
	
	// コンボ数を返す
	return comboCnt;
}

// ノックバックの処理
void APlayerCharacter::KnockBack(float deltaseconds)
{
	// ノックバック中
	if (isKnockBack)
	{
		// プレイヤーを後方に飛ばす
		knockBackPower += deltaseconds;
		float x = UKismetMathLibrary::Ease(POWER_KNOCKBACK, 0.f, knockBackPower, EEasingFunc::ExpoOut);
		AddActorLocalOffset(FVector(x, 0.f, 0.f), true);
		KnockBackTimer();
	}
}

// ロックオン検知内にいる最近距離の敵を取得する
AActor* APlayerCharacter::getNearActor(const TArray<AActor*>& actors)
{
	// ロックオン検知内にいるアクター数を取得する 
	int length = actors.Num();
	if (length != 0)
	{
		// 配列の先頭を最近距離と仮定する
		AActor* nearActor = actors[0];

		for (int i = 1; i < length; i++)
		{
			if (!IsValid(actors[i]))
			{
				continue;
			}
			// よりプレイヤーに近いアクターをnearActorに代入する
			if (nearActor->GetHorizontalDistanceTo(this) > actors[i]->GetHorizontalDistanceTo(this))
			{
				nearActor = actors[i];
			}
		}
		// 最近距離の敵を返す
		return nearActor;
	}
	else 
	{
		// 付近に敵がいない場合
		return NULL;
	}
}
//  lockOnTargetのゲッター
AActor* APlayerCharacter::getLockOnTarget() const
{
	return lockOnTarget;
}


// ノックバックのタイマー処理
void APlayerCharacter::KnockBackTimer()
{
	// ノックバック継続時間内の場合
	if (knockBackTimer < TIME_KNOCKBACK)
	{
		// タイマーをカウントする
		knockBackTimer++;
	}
	else
	{
		// ノックバック処理を終える
		knockBackTimer = 0;
		isKnockBack = false;
	}
}
// 被ダメージ処理
// ダメージ処理を行うかどうかを返す
bool APlayerCharacter::Check_Damaged(AActor* damageHost)
{
	// ダメージ後の無敵時間外かつ回避中でない場合ダメージ処理を行う
	if (isDamaged || isDodge)
	{
		return false;
	}
	// 攻撃フラグをオフにする
	AttackOff();
	knockBackPower = 0;
	
	// ダメージ系フラグをオンにする
	isDamaged = true;
	isKnockBack = true;

	if (IsValid(damageHost))
	{
		// 攻撃を与えてきた相手の方を向く
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FVector(GetActorLocation()), FVector(damageHost->GetActorLocation())));
	}
	return true;
}
// 無敵時間の処理
void APlayerCharacter::InvincibleTimer()
{
	// ダメージを受けている場合処理を行う
	if (!isDamaged)
	{
		return ;
	}
	// タイマーをカウントアップ
	if (invincibleTimer < TIME_INVINCIBLE)
	{
		invincibleTimer++;
	}
	// タイマーが無敵時間を超過した場合
	else
	{
		// Damageフラグとタイマーをリセットする
		isDamaged = false;
		invincibleTimer = 0;
	}
}

