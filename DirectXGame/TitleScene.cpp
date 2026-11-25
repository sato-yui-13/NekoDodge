
#include "TitleScene.h"
#include <Windows.h>
#include <cmath>
#include <numbers>
#include <string>

using namespace KamataEngine;

TitleScene::TitleScene() { camera_ = nullptr; }

TitleScene::~TitleScene() {
	delete title_;
	title_ = nullptr;

	delete changeScene_;
	changeScene_ = nullptr;

	delete backScreen_;
	backScreen_ = nullptr;

	delete camera_;
	camera_ = nullptr;
}

void TitleScene::Initialize() {

	camera_ = new Camera();

	// カメラの初期化
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -20.0f};
	camera_->UpdateMatrix();

	// モデル読み込み
	titleModel_ = Model::CreateFromOBJ("title", true);
	spaceModel_ = Model::CreateFromOBJ("space", true);
	screenModel_ = Model::CreateFromOBJ("titleScreen", true);

	// 背景
	backScreen_ = new BackScreen();

	flourModel_[0] = Model::CreateFromOBJ("square", true);

	// 初期化は1回だけ
	backScreen_->Initialize(flourModel_[0], camera_);

	// タイトル
	title_ = new Title();
	title_->Initialize(titleModel_, spaceModel_, screenModel_, camera_);

	// シーン切り替え演出
	changeScene_ = new changeScene();

	colorfulModel_[0] = Model::CreateFromOBJ("square", true);

	changeScene_->Initialize(colorfulModel_[0], camera_);
}

void TitleScene::Update() {

	// SPACEキーを押したらゲーム開始
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		changeScene_->Start();
	}

	changeScene_->Update();

	backScreen_->Update();
	title_->Update();
}

void TitleScene::Draw() {

	// 3Dタイトル
	Model::PreDraw();

	if (!changeScene_->isStart()) {
		// アニメーション開始前だけ表示
		backScreen_->Draw();
		title_->Draw();
	} else {
		changeScene_->Draw();
	}

	// 背景
	title_->Background();

	Model::PostDraw();
}
