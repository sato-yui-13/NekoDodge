#include "GameScene.h"
#include <random>

using namespace KamataEngine;

GameScene::~GameScene() {}

void GameScene::Initialize() {
	player_ = new player();
	player_->Initialize();

	enemy_ = new Enemy();
	enemy_->Initialize();

	trackingEnemy_ = new TrackingEnemy();
	trackingEnemy_->Initialize();
}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();
	trackingEnemy_->Update();
}

void GameScene::Draw() {

	player_->Draw();
	enemy_->Draw();
	//trackingEnemy_->Draw();
}
