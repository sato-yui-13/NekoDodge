#include "player.h"
#include <Windows.h>
#include <string>

using namespace KamataEngine;

player::~player() {}

void player::Initialize(KamataEngine::Model* playerModel, KamataEngine::Camera* camera) {
	camera_ = camera;

	// プレイヤーモデル
	playerModel_ = playerModel;
	playerWt_.Initialize();
	playerWt_.translation_ = {-10.0f, -7.0f, 0.0f};
	playerWt_.TransferMatrix();
	playerWt_.UpdateMatrix();

	// 登場の初期位置
	isEntrance_ = true;
	entranceStart_.x = playerWt_.translation_.x;
	entranceStart_.y = playerWt_.translation_.y;
}

void player::InputMove() {

	// 左右
	if (Input::GetInstance()->PushKey(DIK_D)) {
		playerWt_.translation_.x += velocity_.x;

		//向き
		playerWt_.rotation_.z = 1.0f;
		direction_.x = 1.0f;
		direction_.y = 0.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_A)) {
		playerWt_.translation_.x -= velocity_.x;

		//向き
		playerWt_.rotation_.z = -1.0f;
		direction_.x = -1.0f;
		direction_.y = 0.0f;

	}

	// 前後
	if (Input::GetInstance()->PushKey(DIK_W)) {
		playerWt_.translation_.y += velocity_.y;


		// 向き
		playerWt_.rotation_.z = -1.0f;
		direction_.x = 0.0f;
		direction_.y = 1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_S)) {
		playerWt_.translation_.y -= velocity_.y;

		// 向き
		playerWt_.rotation_.z = -1.0f;
		direction_.x = 0.0f;
		direction_.y = -1.0f;
	}

	//playerWt_.UpdateMatrix();
}

void player::UpdateEntrance() {

	entranceTimer_ += 1.0f / 60.0f;

	float timer_ = entranceTimer_ / entranceDuration_;

	if (timer_ > 1.0f) {
		timer_ = 1.0f;
		isEntrance_ = false;
	}

	float easeTimer_ = 1.0f - (1.0f - timer_) * (1.0f - timer_);

	float x = entranceStart_.x + (entranceEnd_.x - entranceStart_.x) * easeTimer_;

	float y = entranceStart_.y + (entranceEnd_.y - entranceStart_.y) * easeTimer_;

	playerWt_.translation_.x = x;
	playerWt_.translation_.y = y;


}

#pragma region CheckTutorialInput
// void player::CheckTutorialInput() {

//	if (!isTutorial) {
//
//		if (Input::GetInstance()->PushKey(DIK_D)) {
//			playerWt_.translation_.x += velocity_.x;
//		}
//
//		if (Input::GetInstance()->PushKey(DIK_A)) {
//			playerWt_.translation_.x -= velocity_.x;
//		}
//
//		// 前後
//		if (Input::GetInstance()->PushKey(DIK_W)) {
//			playerWt_.translation_.y += velocity_.y;
//		}
//
//		if (Input::GetInstance()->PushKey(DIK_S)) {
//			playerWt_.translation_.y -= velocity_.y;
//		}
//	}
//}
#pragma endregion

void player::TakeDamage() { hp_--; }
bool player::IsDead() {return hp_ <= 0; }


void player::Update() {
	
	if (isEntrance_) {
		// 入場
		UpdateEntrance();
	} else {
		// キー入力
		InputMove();
		// CheckTutorialInput();
	}

	playerWt_.UpdateMatrix();
}

void player::Draw() { 
	
	playerModel_->Draw(playerWt_, *camera_); 

}


