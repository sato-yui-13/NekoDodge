#pragma once
#include "KamataEngine.h"
#include <random>
#include "player.h"
class Bullet {
public:
	// Bullet();
	~Bullet();

	void Initialize(KamataEngine::WorldTransform* target, KamataEngine::Vector3 position, KamataEngine::Model* ballModel, KamataEngine::Camera* camera, player* player);

	// 初期位置更新
	void SetPosition(KamataEngine::Vector3 position);

	// 当たり判定
	bool CheckCollision();

	// 動く関数呼び出す
	void Update();
	void Draw();

private:
	

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
	//あたっているか
	bool isHit_ = false;
};