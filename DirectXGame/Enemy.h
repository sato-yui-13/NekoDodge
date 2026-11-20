#pragma once
#include "Bullet.h"
#include "KamataEngine.h"
#include "PlayerBullet.h"
#include <vector>

#include <random>

using namespace KamataEngine;

class player;

class Enemy {
public:
	~Enemy();

	enum class AttackType
	{
		Homing, //追尾
		Fan,//扇型
		Rain,//横一列
	};

	void SetAttackType(AttackType type) { attackType_ = type; }

	void Initialize(KamataEngine::Model* enemyModel, KamataEngine::WorldTransform* target, KamataEngine::Camera* camera, player* player, KamataEngine::Vector3 position, bool isFirstEnemy);

	// 入場フラグ
	void UpdateEntrance();

	void Move();

	void Update();
	void Draw();

	// 弾の個数
	void FireBullet();
	//扇
	void FireFanBullet();

	bool IsEntranceFinished() { return isEntranceFinished_; };
	
	//横一列
	void FireRainBullet();

	// 死ぬ
	bool IsDead() const { return isDead_; }
	void TakeDamage();

	void CheckCollision(PlayerBullet* playerBullet);
	KamataEngine::WorldTransform* GetWorldTransform() { return &enemyWt_; }
	// 弾制限
	void SetMaxShotCount(int count) { maxShotCount_ = count; }
	// 早いやつ
	void SetRapidFire(bool isRapid) { isRapidFire_ = isRapid; }




private:
	//初弾
	AttackType attackType_ = AttackType::Homing;


	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//========== Bullet =============
	std::vector<Bullet*> bullets_;
	KamataEngine::WorldTransform* target_;
	KamataEngine::Model* bollModel_;
	player* player_ = nullptr;

	// 連射用
	float attackTimer_ = 0.0f;
	int shotCount_ = 0;
	bool isResting_ = false;
	int maxShotCount_ = 3;

	// 高速発射
	bool isRapidFire_ = false;

	//========= 5の方向用 ===============
	float fanAttackTimer_ = 0.0f;
	//========= 横一列 ===============
	float rainAttackTimer_ = 0.0f;
	bool isRainFired_ = false;

	//========== 敵のモデル ==============
	KamataEngine::Model* enemyModel_;
	KamataEngine::WorldTransform enemyWt_;

	// ボールの出るフラグ
	// bool isLaunched_ = false;
	bool isEntranceFinished_ = false;
	// ボールの速度
	float speed_ = 0.05f;
	// 向き記録
	KamataEngine::Vector2 entranceDirection_;
	bool isFirstEnemy_ = false;
	//====== 死ぬflag ========
	bool isDead_ = false;
};