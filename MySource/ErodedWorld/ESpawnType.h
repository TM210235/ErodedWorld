// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ESpawnType.generated.h"
/**
 * Playerのスポーン位置を決める
 * 
 */
UENUM(BlueprintType)
enum class ESpawnType: uint8
{
	Tutorial,			// チュートリアルステージ
	AdvStart,		// アドベンチャーマップ＃スタート地点
	AdvDrHouse,	// アドベンチャーマップ＃博士の研究室前
	AdvGate,		// アドベンチャーマップ＃ボス扉の前
	BossMap,		// ボスマップ
};