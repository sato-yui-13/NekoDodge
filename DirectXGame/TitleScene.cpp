#include "TitleScene.h"
#include <cmath>
#include <Windows.h>
#include <string>
#include <numbers>

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	
	delete title_;
}

void TitleScene::Initialize(Camera* camera) {

	
    //assert(camera);

	camera_ = camera;

	// カメラ
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -10.0f};
	camera_->rotation_ = {0.0f, 0.0f, 0.0f};

	titleModel_ = Model::CreateFromOBJ("title", true);
	spaceModel_ = Model::CreateFromOBJ("space", true);
	screenModel_ = Model::CreateFromOBJ("titleScreen", true);

			backScreen_ = new BackScreen();

	for (int i = 0; i < 10; i++) {
		flourModel_[i] = Model::CreateFromOBJ("square", true);

		backScreen_->Initialize(flourModel_[i], camera_);
	}

	title_ = new Title();
	title_->Initialize(titleModel_, spaceModel_, screenModel_, camera_);
}

void TitleScene::Update() {
	backScreen_->Update();
	title_->Update(); }


void TitleScene::Draw() {
	
		
	// 3Dタイトル
	Model::PreDraw();
	// 1. 背景を描画（10個の丸）
	if (backScreen_) {
		backScreen_->Draw();
	}

	// 2. タイトルロゴなどを描画（手前に表示）
	if (title_) {
		title_->Draw();
	}
	Model::PostDraw();
}
