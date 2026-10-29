#include "GameOver.h"
#include <Windows.h>

using namespace KamataEngine;
GameOver::GameOver() {}

GameOver::~GameOver() {}

void GameOver::Initialize() {
	//============= 背景 ============
	backgroundModel_ = Model::CreateFromOBJ("titleScreen", true);
	backgroundwt_.Initialize();
	backgroundwt_.UpdateMatrix();


	//============= ゲームオーバー ================
	gOModel_ = Model::CreateFromOBJ("gameOver", true);
	gOwt_.Initialize();
	gOwt_.UpdateMatrix();

	//============= リスタート  ==================
	reStartModel_ = Model::CreateFromOBJ("restart", true);
	reStartwt_.Initialize();
	reStartwt_.UpdateMatrix();

	//============== タイトル =================
	titleModel_ = Model::CreateFromOBJ("reTitle", true);
	titlewt_.Initialize();
	titlewt_.UpdateMatrix();

	

	//============= 色 ==========
	restartColor_.Initialize();

	titleColor_.Initialize();

	//========== カメラ =============
	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = {0.0f, 0.0f, -10.0f};
	camera_->rotation_ = {0.0f, 0.0f, 0.0f};
	camera_->UpdateMatrix();
}

void GameOver::SelectMenu() {

	// W または ↑ → selectIndex_ を 0 にする

	// S または ↓ → selectIndex_ を 1 にする

	if (Input::GetInstance()->PushKey(DIK_W)) {
		selectIndex_ = 0;
	}

	if (Input::GetInstance()->PushKey(DIK_S)) {
		selectIndex_ = 1;
	}
}

int GameOver::ConfirmSelection() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		return selectIndex_;
	}

	return -1;
}


void GameOver::Update() {
	SelectMenu();
	if (selectIndex_ == 0) {
		restartColor_.SetColor({1.0f, 1.0f, 0.0f, 1.0f});
		titleColor_.SetColor({1.0f, 1.0f, 1.0f, 1.0f});
	} else {
		restartColor_.SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		titleColor_.SetColor({1.0f, 1.0f, 0.0f, 1.0f});
	}

	backgroundwt_.UpdateMatrix();
}

void GameOver::Draw() {
	Model::PreDraw();

	backgroundModel_->Draw(backgroundwt_, *camera_);
	gOModel_->Draw(gOwt_, *camera_);
	reStartModel_->Draw(reStartwt_, *camera_, &restartColor_);
	titleModel_->Draw(titlewt_, *camera_, &titleColor_);
	





	Model::PostDraw();
}
