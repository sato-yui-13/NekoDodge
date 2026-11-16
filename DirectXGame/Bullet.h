#pragma once
#include "KamataEngine.h"
#include "player.h"
#include <random>
class Bullet {
public:
	// Bullet();
	~Bullet();

	
	// フラグの定義
	enum class MoveType {
		Homing,
		Straight,
	};



	void Initialize(
	    KamataEngine::WorldTransform* target, KamataEngine::Vector3 position, KamataEngine::Model* ballModel, KamataEngine::Camera* camera, player* player, float speed_, Bullet::MoveType moveType,
	    KamataEngine::Vector2 direction );

	// 初期位置更新
	void SetPosition(KamataEngine::Vector3 position);

	// 直線
	void StraightMove();

	// 当たり判定
	bool CheckCollision();
	bool IsHit() const { return isHit_; }

	// 動く関数呼び出す
	void Update();
	void Draw();

private:
	MoveType moveType_ = MoveType::Homing;
	// 追尾
	void Homing();

	// モデル
	KamataEngine::Model* ballModel_;
	KamataEngine::Camera* camera_ = nullptr;

	// 追尾の位置
	KamataEngine::WorldTransform bulletWt_;
	// プレイヤーの位置
	KamataEngine::WorldTransform* target_;
	// スピード
	float speed = 0.05f;
	// 時間
	float waveTime_ = 0.0f;

	// 速度
	KamataEngine::Vector2 velocity_ = {0.1f, 0.1f};
	// 追いかける位置
	KamataEngine::Vector2 targetPosition_ = {0.0f, 0.0f};

	player* player_;
	// あたっているか
	bool isHit_ = false;

	// 5っの向き
	KamataEngine::Vector2 direction_;
};