
#include "GameManager.h"
#include <Windows.h>

using namespace KamataEngine;

GameManager::GameManager() {}

GameManager::~GameManager() {

	delete gameScene_;
	gameScene_ = nullptr;

	delete gameOver_;
	gameOver_ = nullptr;

	delete gameClear_;
	gameClear_ = nullptr;

	delete titleScene_;
	titleScene_ = nullptr;

	delete whiteSprite_;
	whiteSprite_ = nullptr;
}

// 初期化
void GameManager::Initialize() {

	// 白くなるスプライト
	whiteTextureHandle_ = TextureManager::Load("white1x1.png");
	whiteSprite_ = Sprite::Create(whiteTextureHandle_, {0, 0});
	whiteSprite_->SetSize({1280.0f, 720.0f});

	// カメラ
	camera_.Initialize();
	camera_.translation_ = {0, 0, -20};
	camera_.rotation_.x = 0.2f;
	camera_.UpdateMatrix();

	// 最初のシーンを生成
	ChangeScene();
}

// シーン切り替え
void GameManager::ChangeScene() {

	if (scene_ == oldScene_) {
		return;
	}

	switch (scene_) {

	case Scene::kTitle:

		delete gameOver_;
		gameOver_ = nullptr;

		delete gameClear_;
		gameClear_ = nullptr;

		// カメラを初期位置に戻す
		camera_.Initialize();
		camera_.translation_ = {0, 40, -20};
		camera_.rotation_.x = 0.2f;
		camera_.UpdateMatrix();

		titleScene_ = new TitleScene();
		titleScene_->Initialize();

		break;

	case Scene::kGame:

		delete titleScene_;
		titleScene_ = nullptr;

		delete gameOver_;
		gameOver_ = nullptr;

		delete gameClear_;
		gameClear_ = nullptr;

		gameScene_ = new GameScene();
		gameScene_->Initialize();

		gameTimer_ = 0.0f;
		clearTimer_ = 0.0f;
		isClearEffect_ = false;

		break;

	case Scene::kOver:

		delete gameScene_;
		gameScene_ = nullptr;

		gameOver_ = new GameOver();
		gameOver_->Initialize();

		break;

	case Scene::kClear:

		delete gameScene_;
		gameScene_ = nullptr;

		gameClear_ = new GameClear();
		gameClear_->Initialize();

		break;
	}

	oldScene_ = scene_;
}

// 更新
void GameManager::Update() {

	switch (scene_) {

	case Scene::kTitle:

		titleScene_->Update();

		// アニメーション終了後ゲームへ
		if (titleScene_->IsAnimEnd()) {
			scene_ = Scene::kGame;
			ChangeScene();
			return;
		}

		break;

	case Scene::kGame:

		gameScene_->Update();

		gameTimer_ += 1.0f / 60.0f;

		// 40秒経過したらクリア演出開始
		if (gameTimer_ >= 40.0f && !isClearEffect_) {
			isClearEffect_ = true;
		}

		if (isClearEffect_) {
			clearTimer_ += 1.0f / 60.0f;
		}

		// クリア演出終了
		if (clearTimer_ >= 1.0f) {
			scene_ = Scene::kClear;
			ChangeScene();
			return;
		}

		// プレイヤー死亡演出終了
		if (gameScene_->IsExplosionFinished()) {
			scene_ = Scene::kOver;
			ChangeScene();
			return;
		}

		break;

	case Scene::kOver: {

		gameOver_->Update();

		int selection = gameOver_->ConfirmSelection();

		if (selection == 0) {
			// リスタート
			scene_ = Scene::kGame;
			ChangeScene();
			return;

		} else if (selection == 1) {
			// タイトルへ
			scene_ = Scene::kTitle;
			ChangeScene();
			return;
		}

		break;
	}

	case Scene::kClear:

		gameClear_->Update();

		// SPACEキーでタイトルへ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			scene_ = Scene::kTitle;
			ChangeScene();
		}

		break;
	}
}

// 描画
void GameManager::Draw() {

	switch (scene_) {

	case Scene::kTitle:

		titleScene_->Draw();
		break;

	case Scene::kGame:

		gameScene_->Draw();

		// 白いフェード
		if (isClearEffect_) {
			whiteSprite_->SetColor({1.0f, 1.0f, 1.0f, clearTimer_});

			Sprite::PreDraw();
			whiteSprite_->Draw();
			Sprite::PostDraw();
		}

		break;

	case Scene::kOver:

		gameOver_->Draw();
		break;

	case Scene::kClear:

		gameClear_->Draw();
		break;
	}
}
