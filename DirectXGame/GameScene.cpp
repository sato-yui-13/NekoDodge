#include "GameScene.h"
#include <random>

using namespace KamataEngine;

GameScene::~GameScene() {

	for (Enemy* enemy : enemies_) {
		delete enemy;
	}

	enemies_.clear();
}

void GameScene::Initialize() {
	titleModel_ = Model::CreateFromOBJ("title", true);

	player_ = new player();
	player_->Initialize();




	std::random_device rd;
	std::mt19937 gen(rd());

	// 敵の数 → 1～3体
	std::uniform_int_distribution<int> enemyCountDist(4, 8);

	// 敵のY座標 → ほぼ同じ高さ
	std::uniform_real_distribution<float> enemyYDist(180.0f, 220.0f);

	// 敵のX座標 → 画面内でランダム
	std::uniform_real_distribution<float> enemyXDist(100.0f, 1180.0f);

	int enemyCount = enemyCountDist(gen);

	for (int i = 0; i < enemyCount; i++) {

		Enemy* enemy = new Enemy();

		Vector2 position = {enemyXDist(gen), enemyYDist(gen)};

		enemy->Initialize(position);

		enemies_.push_back(enemy);
	}
	// 背景
	//   背景
	//ScreenHd = TextureManager::Load("Title/screen.png");

	//sprite_ = Sprite::Create(ScreenHd, {0, 0});
}

void GameScene::CheckCollisionEnemy() {

	for (Enemy* enemy : enemies_) {
		for (int i = 0; i < enemy->GetBulletCount(); i++) {
			if (Collision::Check(player_->GetPosition(), player_->GetSize(), enemy->GetBulletPosition(i), enemy->GetSize())) {

				// 敵の弾に当たった
				player_->SetDead();
			}
		}
	}

	if (player_->IsDead()) {

		// 死亡したときの処理
		// げーむおーば
	}
}

void GameScene::Update() {
	player_->Update();
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}




	CheckCollisionEnemy();
}

void GameScene::Draw() {

	Sprite::PreDraw();
	//sprite_->Draw();
	Sprite::PostDraw();

	player_->Draw();
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	// 3Dタイトル
	Model::PreDraw();
	// 背景
	title_->Background();
	Model::PostDraw();
}
