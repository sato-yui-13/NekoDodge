#pragma once
#include "KamataEngine.h"

class TrackingEnemy {
public:
	~TrackingEnemy();

	void Initialize();

	//敵の移動(左)
	void MoveLeft();
	// 敵の移動(右)
	void MoveRight();

	void Update();
	void Draw();

private:
	// ==== 左の敵 ====
	// 位置
	KamataEngine::Vector2 enemyLeft_ = {-100.0f, 100.0f};
	// 敵を止めたい位置
	KamataEngine::Vector2 targetLeft_ = {480.0f, 100.0f};
	// 走る速度
	float LeftSpeed_ = 5.0f;
	//====== 画像 ======
	// Leftのスプライト
	KamataEngine::Sprite* left_ = nullptr;
	// Leftのテクスチャ
	uint32_t LeftHd = 0;

	//============ 左の弾 ============
	//位置
	KamataEngine::Vector2 bulletLeft_ = {0.0f, 0.0f};
	// 時間
	float LeftTimer_ = 0.0f;
	// 時間のフラグ
	bool isLeft_ = false;
	//スピード
	float bulletLeftSpeed_=1.0f;



	//==== 右の敵 ====
	// 位置
	KamataEngine::Vector2 enemyRight_ = {1380.0f, 100.0f};
	// 敵を止めたい位置
	KamataEngine::Vector2 targetRight_ = {800.0f, 100.0f};
	// 走る速度
	float RightSpeed_ = 5.0f;
	//====== 画像 ======
	// Leftのスプライト
	KamataEngine::Sprite* right_ = nullptr;
	// Leftのテクスチャ
	uint32_t RightHd = 0;

	//============ 右の弾 ===========
	// 位置

	// 時間
	float RightTimer_ = 0.0f;
	// 時間のフラグ
	bool isRight_ = false;
	// スピード


};
