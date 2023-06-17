// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"


class UAbilitySystemComponent;
class UGameplayAbility;

// キャラクター基底クラス
// GamePlayAbilitiesの設定を持つ

UCLASS()
class ERODEDWORLD_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// コンストラクタ
	ACharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// スポーン時の処理
	virtual void BeginPlay() override;

public:	
	// 毎フレームの処理
	virtual void Tick(float DeltaTime) override;
	// Inputに処理を割り当てるためのセットアップ
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// GameAbilityComponent キャラクターのコンボや回避アクションのために活用
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
		UAbilitySystemComponent* AbilitySystemComp;
	    UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// 攻撃しているかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAttack;
	// ダメージを受けているかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDamaged;
	// アクション中かどうか（その他の行動を制限するフラグ）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isAction;

public:
	// 
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void OnRep_Controller() override;

// ------------------GamePlayAbilitiesを使用するために必要なもの------------------
public:
	// GameplayAbility を持つ配列
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;
public:
	// ゲームスタート時のAbilityを付与する処理
	void AddStartupGameplayAbilities();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int32 ExistsLevel = 1;
	
	// GameAbilitySystem初期化フラグ
	UPROPERTY()
		int32 bAbilitiesInitialzied;
// ------------------GamePlayAbilitiesを使用するために必要なもの------------------

};

