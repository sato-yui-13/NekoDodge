
#pragma once
#include "Bullet.h"
#include "KamataEngine.h"
#include "PlayerBullet.h"
#include <vector>

using namespace KamataEngine;

class player;

class Enemy {
public:
	~Enemy();

	enum class AttackType {
		Homing, // 追尾
		Fan,    // 扇型
		Rain,   // 横一列
	};

	void SetAttackType(AttackType type) { attackType_ = type; }

	void Initialize(KamataEngine::Model* enemyModel, KamataEngine::Camera* camera, player* player, KamataEngine::Vector3 position, bool isFirstEnemy);

	void UpdateEntrance();
	void Move();
	void Update();
	void Draw();

	// 攻撃
	void FireBullet();
	void FireFanBullet();
	void FireRainBullet();

	// 入場
	bool IsEntranceFinished() const { return isEntranceFinished_; }

	// 死亡
	bool IsDead() const { return isDead_; }
	void TakeDamage();

	void CheckCollision(PlayerBullet* playerBullet);

	// 敵の現在位置を取得（読み取り専用）
	KamataEngine::Vector3 GetPosition() const { return enemyWt_.translation_; }

	// 弾制限
	void SetMaxShotCount(int count) { maxShotCount_ = count; }

	// 高速発射
	void SetRapidFire(bool isRapid) { isRapidFire_ = isRapid; }

private:
	// 攻撃タイプ
	AttackType attackType_ = AttackType::Homing;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// Bullet
	std::vector<Bullet*> bullets_;
	KamataEngine::Model* bollModel_ = nullptr;
	player* player_ = nullptr;

	// 連射用
	float attackTimer_ = 0.0f;
	int shotCount_ = 0;
	bool isResting_ = false;
	int maxShotCount_ = 3;

	// 高速発射
	bool isRapidFire_ = false;

	// Fan攻撃
	float fanAttackTimer_ = 0.0f;

	// Rain攻撃
	float rainAttackTimer_ = 0.0f;
	bool isRainFired_ = false;

	// 敵のモデル
	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::WorldTransform enemyWt_;

	// 入場
	bool isEntranceFinished_ = false;
	float speed_ = 0.05f;
	KamataEngine::Vector2 entranceDirection_;
	bool isFirstEnemy_ = false;

	// 死亡フラグ
	bool isDead_ = false;
};
