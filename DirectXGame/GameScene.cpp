#include "GameScene.h"
#include <random>

    using namespace KamataEngine;

GameScene::~GameScene() {
	delete enemy_;
	enemy_ = nullptr;

	delete enemyModel_;
	enemyModel_ = nullptr;

	delete bulletModel_;
	bulletModel_ = nullptr;
}

void GameScene::Initialize() {

	// 敵と弾のモデルを作成
	enemyModel_ = Model::CreateFromOBJ("flour", true);
	bulletModel_ = Model::CreateFromOBJ("boll", true);

	// 敵を生成して初期化
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, bulletModel_, camera_, enemyPosition_);
}

void GameScene::CheckCollisionEnemy() {
	// いったん衝突判定は保留
}

void GameScene::Update() {
	if (enemy_) {
		enemy_->Update();
	}

	CheckCollisionEnemy();
}

void GameScene::Draw() {
	Model::PreDraw();

	if (enemy_) {
		enemy_->Draw();
	}

	Model::PostDraw();
}
