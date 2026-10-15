
#pragma once

#include "KamataEngine.h"
#include <random>

class Enemy {
public:
	~Enemy();

	void Initialize(KamataEngine::Model* enemyModel, KamataEngine::Model* bulletModel, KamataEngine::Camera* camera, KamataEngine::Vector2 position);

	void Update();
	void Draw();

	void Move();

	KamataEngine::Vector2 GetBulletPosition(int index);
	KamataEngine::Vector2 GetSize();
	int GetBulletCount();

private:
	void StartAttack();
	void SpawnNextBullet();
	void UpdateAttack();
	void PrepareNextAttack();
	void SyncTransforms();

	// 3D描画用
	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::Model* bulletModel_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::WorldTransform enemyWt_;
	KamataEngine::WorldTransform bulletWt_[8];

	// 2Dゲームロジック用
	KamataEngine::Vector2 enemyPosition_ = {100.0f, 100.0f};
	KamataEngine::Vector2 nextEnemyPosition_ = {};
	KamataEngine::Vector2 bulletPosition[8] = {};
	KamataEngine::Vector2 bulletVelocity[8] = {};

	KamataEngine::Vector2 size_ = {4.0f, 4.0f};

	// 攻撃管理
	int attackType_ = 1;
	int bulletsSpawned_ = 0;
	int bulletsToSpawn_ = 0;

	bool bulletActive_[8] = {};
	bool attackStarted_ = false;
	bool isEnemyMoving_ = false;
	bool isSplit_ = false;

	float enemyTimer_ = 0.0f;
	float bulletSpawnTimer_ = 0.0f;
	float enemyMoveTimer_ = 0.0f;
	float splitTimer_ = 0.0f;

	float bulletSpeed_ = 5.0f;
	float enemySpeed_ = 5.0f;

	bool enemyVisible_ = true;

	std::mt19937 randomEngine_{std::random_device{}()};
};
