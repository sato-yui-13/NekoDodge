#include "GameScene.h"
#include <algorithm>
#include <cfloat>
#include <random>

using namespace KamataEngine;

GameScene::GameScene() {
	// ポインタの安全な初期化
	camera_ = nullptr;
	// enemy_ = nullptr;
	enemyModel_ = nullptr;
	backgroundModel_ = nullptr;
	particleModel_ = nullptr;
}

GameScene::~GameScene() {
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	enemies_.clear();

	delete enemyModel_;
	enemyModel_ = nullptr;

	// ★追加：カメラの解放
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

	// delete bulletModel_;
	// bulletModel_ = nullptr;
}

void GameScene::Initialize() {
	//============= 背景 ============
	backgroundModel_ = Model::CreateFromOBJ("titleScreen", true);
	backgroundTransform_.Initialize();
	backgroundTransform_.UpdateMatrix();

	//========== カメラ =============
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -10.0f};
	camera_->rotation_ = {0.0f, 0.0f, 0.0f};
	camera_->UpdateMatrix();

	//========= player ===========
	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new player();
	player_->Initialize(playerModel_, camera_);
	target_ = player_->GetWorldTransform();
	//======== 敵 ============
	enemyModel_ = Model::CreateFromOBJ("flour", true);
	enemiesPerWave_ = 1;
	CreateEnemy();

	//=============== パーティクル ================
	//	particles_ = new Particle();
	particleModel_ = Model::CreateFromOBJ("boll", true);
}

bool GameScene::IsPlayerDead() const { return isPlayerDead_; }

bool GameScene::IsExplosionFinished() const { return isPlayerDead_ && particles_.empty(); }

void GameScene::CreateEnemy() {
	// 8方向
	Vector3 spawnPositions[8] = {
	    {-5.0f,  5.0f,  0.0f}, // 左
	    {10.0f,  0.0f,  0.0f}, // 右
	    {0.0f,   5.0f,  0.0f}, // 上
	    {0.0f,   -1.0f, 0.0f}, // 下
	    {-5.0f, 1.0f,  0.0f}, // 左上
	    {5.0f,  1.0f,  0.0f}, // 右上
	    {-5.0f, -1.0f, 0.0f}, // 左下
	    {5.0f,  -1.0f, 0.0f}  // 右下
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

		enemy->Initialize(enemyModel_, target_, camera_, player_, position, enemySpawnCount_ == 0);

		if (enemySpawnCount_ == 0) {

			enemy->SetMaxShotCount(1);

		} else if (enemySpawnCount_ == 1) {

			enemy->SetMaxShotCount(3);

		} else if (enemySpawnCount_ == 2) {

			enemy->SetRapidFire(true);

		} else if (enemySpawnCount_ == 3) {

			enemy->SetAttackType(Enemy::AttackType::Fan);
		}

		enemySpawnCount_++;

		enemies_.push_back(enemy);
	}
}

void GameScene::Update() {
	gameTimer_ += 1.0f / 60.0f;
	float minDistance = FLT_MAX;
	Enemy* nearestEnemy = nullptr;

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

	// player_->Update();

	// 死んだか
	if (player_->IsDead() && !isPlayerDead_) {
		isPlayerDead_ = true;
		Vector3 position = player_->GetWorldTransform()->translation_;

		// 分散
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

	if (!player_->IsEntrance() && !isEnemyEntranceStarted_) {
		// 敵の入場開始処理
		isEnemyEntranceStarted_ = true;
	}

	for (Enemy* enemy : enemies_) {
		if (isEnemyEntranceStarted_) {
			if (!enemy->IsEntranceFinished()) {
				enemy->UpdateEntrance();
			} else {
				enemy->Update();
			}
		}
		// ここで1体ずつ処理する
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
	} // ← ここで当たり判定ループ終了！

	// 敵の削除・次の敵の生成
	if (!enemies_.empty() && enemies_[0]->IsDead()) {
		delete enemies_[0];
		enemies_.erase(enemies_.begin());
		CreateEnemy();
	}

	for (Enemy* enemy : enemies_) {
		// 敵との距離を調べる

		if (enemy->IsDead()) {
			continue;
		}

		Vector3 playerPosition = player_->GetWorldTransform()->translation_;
		Vector3 enemyPosition = enemy->GetWorldTransform()->translation_;

		float dx = enemyPosition.x - playerPosition.x;
		float dy = enemyPosition.y - playerPosition.y;

		float distance = sqrt(dx * dx + dy * dy);

		if (distance < minDistance) {
			minDistance = distance;
			nearestEnemy = enemy;
		}
	}
	if (nearestEnemy != nullptr) {

		player_->SetTargetPosition(nearestEnemy->GetWorldTransform()->translation_);
	}
	// ここ！
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
