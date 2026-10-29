#include "TitleScene.h"
#include <Windows.h>
#include <cmath>
#include <numbers>
#include <string>

using namespace KamataEngine;

TitleScene::TitleScene() {
	// コンストラクタで nullptr 初期化しておくと安全です
	camera_ = nullptr;
}

TitleScene::~TitleScene() {
	delete title_;
	delete changeScene_;
	delete backScreen_;
	delete camera_; 
}

void TitleScene::Initialize() {


	camera_ = new Camera();

	// カメラの初期化
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -20.0f};
	camera_->UpdateMatrix();
	titleModel_ = Model::CreateFromOBJ("title", true);
	spaceModel_ = Model::CreateFromOBJ("space", true);
	screenModel_ = Model::CreateFromOBJ("titleScreen", true);

	backScreen_ = new BackScreen();
	for (int i = 0; i < 10; i++) {
		flourModel_[i] = Model::CreateFromOBJ("square", true);

		// ※注意点：現在ループ内で10回同じ backScreen_ に対して Initialize を呼んでいます。
		// もし flourModel_ を配列表記で渡す設計であれば、ループの外で行うか仕様を確認してください。
		backScreen_->Initialize(flourModel_[i], camera_);
	}

	title_ = new Title();
	title_->Initialize(titleModel_, spaceModel_, screenModel_, camera_);

	changeScene_ = new changeScene();

	colorfulModel_[0] = Model::CreateFromOBJ("square", true);

	changeScene_->Initialize(colorfulModel_[0], camera_);
}
void TitleScene::Update() {

	// SPACEキーを押したらゲーム開始
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		changeScene_->Start();
		// isStart_ = true;
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
