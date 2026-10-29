#include "GameScene.h"
#include <algorithm>
#include <random>

using namespace KamataEngine;

GameScene::GameScene() {
	// ポインタの安全な初期化
	camera_ = nullptr;
	enemy_ = nullptr;
	enemyModel_ = nullptr;
	backgroundModel_ = nullptr;
	particleModel_ = nullptr;
}

GameScene::~GameScene() {
	delete enemy_;
	enemy_ = nullptr;

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
	KamataEngine::WorldTransform* target_ = player_->GetWorldTransform();

	//======== 敵 ============
	// 敵と弾のモデル
	enemyModel_ = Model::CreateFromOBJ("flour", true);
	// bollModel_ = Model::CreateFromOBJ("boll", true);
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, target_, camera_, player_);

	//=============== パーティクル ================
	//	particles_ = new Particle();
	particleModel_ = Model::CreateFromOBJ("boll", true);
}

bool GameScene::IsPlayerDead() const { return isPlayerDead_; }

bool GameScene::IsExplosionFinished() const { return isPlayerDead_ && particles_.empty(); }


void GameScene::Update() {

	// for (Particle* particle : particles_) {
	//	particle->Update();
	// }

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

	player_->Update();

	//死んだか
	if (player_->IsDead() && !isPlayerDead_) {
		isPlayerDead_ = true;
		Vector3 position = player_->GetWorldTransform()->translation_;

		//分散
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

	if (isEnemyEntranceStarted_) {
		if (!enemy_->IsEntranceFinished()) {
			enemy_->UpdateEntrance();
		} else {
			enemy_->Update();
		}
	}
}

void GameScene::Draw() {
	Model::PreDraw();

	backgroundModel_->Draw(backgroundTransform_, *camera_);
	enemy_->Draw();
	if (!isPlayerDead_) {
		player_->Draw();
	}

	for (Particle* particle : particles_) {
		particle->Draw();
	}

	Model::PostDraw();
}
