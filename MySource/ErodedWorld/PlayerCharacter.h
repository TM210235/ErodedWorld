// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ErodedWorldCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.generated.h"

 
// プレイヤーキャラクタークラス

UCLASS()
class ERODEDWORLD_API APlayerCharacter : public AErodedWorldCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
public:
	virtual void Tick(float DeltaTime) override;


protected:
	// 必殺技ゲージの最大値
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float MAX_VPOINT;
	
	// 基礎攻撃力
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float BASE_ATTACK;
	
	// コンボ時の攻撃倍率 　コンボ数 / COMBO_RAR_RATE
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_COMBO_RAR;

	// 特殊攻撃の攻撃倍率
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_SPATTACK;
	// 必殺技の攻撃倍率
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RATE_VATTACK;
	// ノックバックの力
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float POWER_KNOCKBACK;
	// ダッシュアタックが発生する距離
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float RANGE_DASHATTACK;
	// 時間経過で減少する必殺技ポイントの値
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float LOST_VPOINT;
	// 1ヒットごとに加算される必殺技ポイントの値
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		float ADD_VPOINT;
	// コンボが継続するフレーム
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_COMBO;
	// スキルポイントが自動回復するまでの時間
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_SPOINT_HEAL;
	// 必殺技レベルの上限
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int MAX_VLEVEL;
	// ノックバックしている時間
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_KNOCKBACK;
	// 攻撃を受けた後の無敵時間
	UPROPERTY(BlueprintReadOnly, Category = "Const")
		int TIME_INVINCIBLE;

public:
	// アニメーションによる移動中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAnimMove;
	
	// 検知範囲内の敵に照準が設定されているかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isLockOn;
	
	// 回避中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDodge;
	
	// 会話中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool canTalk;
	// 必殺技レベルが最大かどうか。最大時は必殺技ゲージが時間経過で減少しない
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isVLevelMax;
	
	// ノックバック中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isKnockBack;
	// 死亡しているかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDead;
	// コンボ中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isCombo;
	// 攻撃のキャンセルを受け付けるかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool cantCancel;
	// アクションボタンの連打防止フラグ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isActionBlock;
	// 思念やアイテムのメッセージを表示中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isReport;
	// ボタンガイドを表示中かどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isGuide;
	// 現在のノックバック値
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float knockBackPower;
	// コンボによる攻撃倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float comboRate;
	// アニメーションのタイマー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		float animTimer;
	// 必殺技ゲージ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		float vPoint;
	// コンボ継続用のタイマー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int comboTimer;
	// 特殊ゲージ自動回復用のタイマー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int autoHealSpTimer;
	// 現在の必殺技レベル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int currentVLevel;
	// コンボカウント用変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
		int comboCnt;
	// 無敵時間用タイマー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int invincibleTimer;
	// ノックバック用タイマー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int knockBackTimer;
	// ロックオンターゲット用の変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* lockOnTarget;


	// 攻撃可能状態かどうかを返す
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_Attack();
	// 必殺技可能状態かどうかを返す
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_VAttack();
	// アクション可能状態かどうかを返す
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Can_Action();
	// コンボ継続判定を調べる
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool is_ComboKeep();
	// アクションフラグを切り替える
	UFUNCTION(BlueprintCallable, Category = "Func")
		void SwitchAction();
	// 攻撃フラグを切る
	UFUNCTION(BlueprintCallable, Category = "Func")
		void AttackOff();
	// 時間経過で減少する必殺技ゲージの処理
	UFUNCTION(BlueprintCallable, Category = "Lost")
		void LostVPoint();
	// 必殺技ゲージの増加処理
	UFUNCTION(BlueprintCallable, Category = "Add")
		void AddVPoint();
	// UI更新用 必殺技ゲージの割合
	UFUNCTION(BlueprintCallable, Category = "Get")
		float GetVPointPerMaxVPoint();
	// ノックバック処理
	UFUNCTION(BlueprintCallable, Category = "Func")
		void KnockBack(float deltaseconds);
	
	// コンボのカウントアップ処理
	UFUNCTION(BlueprintCallable, Category = "Count")
		float ComboCntUp();
	
	// ノックバックの時間計測処理
	UFUNCTION(BlueprintCallable, Category = "Timer")
		void KnockBackTimer();
	
	// ダメージ処理を行ったかどうかを取得
	UFUNCTION(BlueprintCallable, Category = "Get")
		bool Check_Damaged(AActor* damageHost);
	
	void InvincibleTimer();
	
	// 一番近くにいる敵を取得する
	UFUNCTION(BlueprintCallable, Category = "Get")
		AActor* getNearActor(const TArray<AActor*>& actors);

	// lockOnTargetのゲッター
	AActor* getLockOnTarget() const;
};
