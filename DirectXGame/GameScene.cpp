#include "GameScene.h"
#include <random>

using namespace KamataEngine;

GameScene::GameScene() {
	// ポインタの安全な初期化
	camera_ = nullptr;
	enemy_ = nullptr;
	enemyModel_ = nullptr;
	backgroundModel_ = nullptr;
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
	//bollModel_ = Model::CreateFromOBJ("boll", true);
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, target_, camera_, player_);

}

void GameScene::Update() {
	player_->Update();
	
	
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
	player_->Draw(); 
	Model::PostDraw();
}
