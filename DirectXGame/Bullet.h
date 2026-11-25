
#pragma once
#include "KamataEngine.h"
#include "player.h"
#include <random>

class Bullet {
public:
	~Bullet();

	enum class MoveType {
		Homing,
		Straight,
	};

	void Initialize(
	    KamataEngine::Vector3 position, KamataEngine::Model* ballModel, KamataEngine::Camera* camera, player* player, float speed_, Bullet::MoveType moveType, KamataEngine::Vector2 direction);

	// 初期位置更新
	void SetPosition(KamataEngine::Vector3 position);

	// 直線
	void StraightMove();

	// 当たり判定
	bool CheckCollision();
	bool IsHit() const { return isHit_; }

	void Update();
	void Draw();

private:
	MoveType moveType_ = MoveType::Homing;

	// 追尾
	void Homing();

	// モデル
	KamataEngine::Model* ballModel_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	// 弾の位置
	KamataEngine::WorldTransform bulletWt_;

	// スピード
	float speed = 0.05f;

	// 時間
	float waveTime_ = 0.0f;

	// 速度
	KamataEngine::Vector2 velocity_ = {0.1f, 0.1f};

	// 追尾するプレイヤー
	player* player_ = nullptr;

	// 当たっているか
	bool isHit_ = false;

	// 直線弾の向き
	KamataEngine::Vector2 direction_;
};
