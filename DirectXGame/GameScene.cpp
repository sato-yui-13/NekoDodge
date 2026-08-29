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


	//背景
	//  背景
	ScreenHd = TextureManager::Load("Title/screen.png");

	sprite_ = Sprite::Create(ScreenHd, {0, 0});
}

void GameScene::CheckCollisionEnemy() {

	// プレイヤーと敵の当たり判定を書く
	if (Collision::Check(player_->GetPosition(), player_->GetSize(), enemy_->GetPosition(), enemy_->GetSize())) {
		// 当たった時の処理
		player_->SetDead();
	}

	if (player_->IsDead()) {

		// 死亡したときの処理
		//げーむおーば

	}
}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();
	trackingEnemy_->Update();

	CheckCollisionEnemy();
}

void GameScene::Draw() {
	
	Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();


	player_->Draw();
	enemy_->Draw();
	//trackingEnemy_->Draw();

	

}
