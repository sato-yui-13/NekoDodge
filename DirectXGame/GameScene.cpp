
#include "GameScene.h"
#include <algorithm>
#include <cfloat>
#include <random>

using namespace KamataEngine;

GameScene::GameScene() {
	camera_ = nullptr;
	enemyModel_ = nullptr;
	backgroundModel_ = nullptr;
	particleModel_ = nullptr;
}

GameScene::~GameScene() {
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	enemies_.clear();

	delete player_;
	player_ = nullptr;

	delete playerModel_;
	playerModel_ = nullptr;

	delete enemyModel_;
	enemyModel_ = nullptr;

	delete camera_;
	camera_ = nullptr;

	delete backgroundModel_;
	backgroundModel_ = nullptr;

	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();

	delete particleModel_;
	particleModel_ = nullptr;
}

void GameScene::Initialize() {

	// 背景
	backgroundModel_ = Model::CreateFromOBJ("titleScreen", true);
	backgroundTransform_.Initialize();
	backgroundTransform_.UpdateMatrix();

	// カメラ
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -10.0f};
	camera_->rotation_ = {0.0f, 0.0f, 0.0f};
	camera_->UpdateMatrix();

	// プレイヤー
	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new player();
	player_->Initialize(playerModel_, camera_);

	// 敵
	enemyModel_ = Model::CreateFromOBJ("flour", true);
	enemiesPerWave_ = 1;
	CreateEnemy();

	// パーティクル
	particleModel_ = Model::CreateFromOBJ("boll", true);
}

bool GameScene::IsPlayerDead() const { return isPlayerDead_; }

bool GameScene::IsExplosionFinished() const { return isPlayerDead_ && particles_.empty(); }

void GameScene::CreateEnemy() {

	// 8方向
	Vector3 spawnPositions[8] = {
	    {-5.0f, 5.0f,  0.0f},
        {10.0f, 0.0f,  0.0f},
        {0.0f,  5.0f,  0.0f},
        {0.0f,  -1.0f, 0.0f},
        {-5.0f, 1.0f,  0.0f},
        {5.0f,  1.0f,  0.0f},
        {-5.0f, -1.0f, 0.0f},
        {5.0f,  -1.0f, 0.0f}
    };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 7);

	for (int i = 0; i < enemiesPerWave_; i++) {

		int randomIndex = dist(gen);

		Enemy* enemy = new Enemy();

		Vector3 position;

		if (enemySpawnCount_ == 0) {
			position = {-14.0f, 0.0f, 0.0f};
		} else {
			position = spawnPositions[randomIndex];
		}

		enemy->Initialize(enemyModel_, camera_, player_, position, enemySpawnCount_ == 0);

		if (enemySpawnCount_ == 0) {
			enemy->SetMaxShotCount(1);

		} else if (enemySpawnCount_ == 1) {
			enemy->SetMaxShotCount(3);

		} else if (enemySpawnCount_ == 2) {
			enemy->SetRapidFire(true);

		} else if (enemySpawnCount_ == 3) {
			enemy->SetAttackType(Enemy::AttackType::Fan);

		} else if (enemySpawnCount_ == 4) {
			enemy->SetAttackType(Enemy::AttackType::Rain);
		}

		enemySpawnCount_++;

		enemies_.push_back(enemy);
	}
}

void GameScene::Update() {

	gameTimer_ += 1.0f / 60.0f;

	float minDistance = FLT_MAX;
	Enemy* nearestEnemy = nullptr;

	// パーティクル更新
	for (Particle* particle : particles_) {
		particle->Update();
	}

	particles_.erase(
	    std::remove_if(
	        particles_.begin(), particles_.end(),
	        [](Particle* particle) {
		        if (particle->IsDead()) {
			        delete particle;
			        return true;
		        }
		        return false;
	        }),
	    particles_.end());

	// プレイヤー死亡判定
	if (player_->IsDead() && !isPlayerDead_) {

		isPlayerDead_ = true;

		Vector3 position = player_->GetPosition();

		Vector3 velocities[8] = {
		    {0.01f,  0.01f,  0.0f},
            {0.0f,   0.01f,  0.0f},
            {-0.01f, 0.01f,  0.0f},
            {0.01f,  0.0f,   0.0f},
            {-0.01f, 0.0f,   0.0f},
            {0.01f,  -0.01f, 0.0f},
            {0.0f,   -0.01f, 0.0f},
            {-0.01f, -0.01f, 0.0f}
        };

		for (int i = 0; i < 8; i++) {
			Particle* particle = new Particle();
			particle->Initialize(particleModel_, camera_, position, velocities[i]);
			particles_.push_back(particle);
		}
	}

	// 敵の入場開始
	if (!player_->IsEntrance() && !isEnemyEntranceStarted_) {
		isEnemyEntranceStarted_ = true;
	}

	// 敵更新
	for (Enemy* enemy : enemies_) {

		if (isEnemyEntranceStarted_) {

			if (!enemy->IsEntranceFinished()) {
				enemy->UpdateEntrance();
			} else {
				enemy->Update();
			}
		}
	}

	// 当たり判定
	for (Enemy* enemy : enemies_) {

		if (enemy->IsDead()) {
			continue;
		}

		for (PlayerBullet* bullet : player_->GetPlayerBullets()) {

			enemy->CheckCollision(bullet);

			if (enemy->IsDead()) {
				break;
			}
		}
	}

	// 敵の削除・次の敵の生成
	if (!enemies_.empty() && enemies_[0]->IsDead()) {

		delete enemies_[0];
		enemies_.erase(enemies_.begin());

		CreateEnemy();
	}

	// 一番近い敵を探す
	for (Enemy* enemy : enemies_) {

		if (enemy->IsDead()) {
			continue;
		}

		Vector3 playerPosition = player_->GetPosition();
		Vector3 enemyPosition = enemy->GetPosition();

		float dx = enemyPosition.x - playerPosition.x;
		float dy = enemyPosition.y - playerPosition.y;

		float distance = sqrt(dx * dx + dy * dy);

		if (distance < minDistance) {
			minDistance = distance;
			nearestEnemy = enemy;
		}
	}

	// 攻撃対象を設定
	if (nearestEnemy != nullptr) {
		player_->SetTargetPosition(nearestEnemy->GetPosition());
	}

	player_->Update();
}

void GameScene::Draw() {

	Model::PreDraw();

	backgroundModel_->Draw(backgroundTransform_, *camera_);

	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	if (!isPlayerDead_) {
		player_->Draw();
	}

	for (Particle* particle : particles_) {
		particle->Draw();
	}

	Model::PostDraw();
}
