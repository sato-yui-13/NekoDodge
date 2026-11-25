
#pragma once
#include "KamataEngine.h"
#include "math/Matrix4x4.h"
#include "math/Vector3.h"

#include "PlayerBullet.h"
#include <vector>

class player {
public:
	~player();

	void Initialize(KamataEngine::Model* playerModel, KamataEngine::Camera* camera);

	// キー入力
	void InputMove();

	// 攻撃
	void Attack();

	// 入場
	void UpdateEntrance();
	bool IsEntrance() { return isEntrance_; }

	// HP
	void TakeDamage();
	bool IsDead();

	void Update();
	void Draw();

	// 弾の取得（読み取り専用）
	const std::vector<PlayerBullet*>& GetPlayerBullets() const { return playerBullets_; }

	// 現在位置の取得（読み取り専用）
	KamataEngine::Vector3 GetPosition() const { return playerWt_.translation_; }

	// 狙うやつ
	void SetTargetPosition(KamataEngine::Vector3 position);

private:
	// プレイヤーのモデル
	KamataEngine::Model* playerModel_;
	KamataEngine::WorldTransform playerWt_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 速度
	KamataEngine::Vector2 velocity_ = {0.1f, 0.1f};

	// 向き
	KamataEngine::Vector2 direction_ = {0.0f, 1.0f};

	// 入場
	bool isEntrance_ = false;
	KamataEngine::Vector2 entranceStart_ = {-10.0f, -7.0f};
	KamataEngine::Vector2 entranceEnd_ = {0.0f, 0.0f};
	float entranceTimer_ = 0.0f;
	float entranceDuration_ = 1.0f;

	// チュートリアル
	bool isTutorial = false;

	// HP
	int hp_ = 6;

	// プレイヤー弾
	std::vector<PlayerBullet*> playerBullets_;
	KamataEngine::Model* playerBulletModel_ = nullptr;

	// 狙うやつ
	KamataEngine::Vector3 targetPosition_ = {0.0f, 0.0f, 0.0f};

	// 無敵時間
	float invincibleTimer_ = 0.0f;

	// 被弾点滅
	float damageTimer_ = 0.0f;
	float blinkTimer_ = 0.0f;
	bool isVisible_ = true;
};
