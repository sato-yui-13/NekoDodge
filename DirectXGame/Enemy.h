#pragma once
#include "KamataEngine.h"
#include <random>

using namespace KamataEngine;
class Enemy {
public:
	~Enemy();

	void Initialize(KamataEngine::Vector2 position);
	
	void Update();
	void Draw();

	// 移動の処理
	void Move();

	//Bulletの処理
	void Bullet();

	//二回目の弾
	void Second();

	//三回目の弾(扇型)
	void Third();

	//四回目の弾(分裂)
	void Fourth();
	// 8方向弾
	void Eight();

	int GetBulletCount();

	//位置
	KamataEngine::Vector2 GetBulletPosition(int index);
	// 当たり判定
	KamataEngine::Vector2 GetSize();

private:

	// 今どの攻撃をするか
	int attackType_ = 1;

	// 当たり判定用の変数
	KamataEngine::Vector2 size_ = {4.0f, 4.0f};
	
	//攻撃
	KamataEngine::Vector2 bulletPosition[8];
	//時間で弾出る
	float enemyTimer_ = 0.0f;
	//時間のflag
	bool isTimer_ = false;
	//speed
	float bulletSpeed_ = 5.0f;
	// 弾の速度（3発分）
	KamataEngine::Vector2 bulletVelocity[8];



	// enemyのスプライト
	KamataEngine::Sprite* spriteBullet[8] = {};
	// enemyのテクスチャ
	uint32_t bulletHd = 0;

	//敵の位置
	KamataEngine::Vector2 enemyPosition = {100.0f, 100.0f};
	// 敵を止めたい位置
	//KamataEngine::Vector2 targetEnemy_ = {630.0f, 100.0f};
	// 
	float moveDirection_ = 1.0f;
	//スピード
	float enemySpeed_ = 6.0f;

	//四回目の宣言
	//開始のflag
	bool isSplitActive_ = false;
	//分裂のタイマー
	float splitTimer_ = 0.0f;
	//分裂できたかどうかのフラグ
	bool isSplit_ = false;
	


	//============== 二個目移行のフラグ ==============//
	
	//描画フラグ
	bool isBulletActive_ = false;

	bool allOut = false;

	// 敵を移動させる
	bool isEnemyMoving_ = false;
	float enemyMoveTimer_ = 0.0f;

	// 移動先
	KamataEngine::Vector2 nextEnemyPosition_;

	// 画像
	// enemyのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// enemyのテクスチャ
	uint32_t enemyHd = 0;
};
