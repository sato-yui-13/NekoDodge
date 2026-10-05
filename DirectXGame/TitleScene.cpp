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

	
    assert(camera);

	camera_ = camera;

	// カメラを初期化
	camera_->Initialize();
	// プレイヤーに近いカメラ位置
	camera_->translation_ = {0.0f, 0.0f, -10.0f};

	// カメラの向き
	camera_->rotation_ = {0.0f, 0.0f, 0.0f};

	titleModel_ = Model::CreateFromOBJ("title", true);
	

	spaceModel_ = Model::CreateFromOBJ("space", true);
	
	screenModel_ = Model::CreateFromOBJ("titleScreen", true);

	title_ = new Title();
	title_->Initialize(titleModel_, spaceModel_, screenModel_, camera_);

}

void TitleScene::Update() { title_->Update(); }
void TitleScene::Draw() {
	
		
	// 3Dタイトル
	Model::PreDraw();

	title_->Draw();

	Model::PostDraw();
}
