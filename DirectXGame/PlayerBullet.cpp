#include "PlayerBullet.h"

void PlayerBullet::Initialize(KamataEngine::Model* playerBollModel, KamataEngine::Camera* camera, KamataEngine::Vector2 direction, KamataEngine::Vector3 position) {

	camera_ = camera;
	direction_ = direction;

	// モデル
	playerBollModel_ = playerBollModel;
	playerBollWt_.Initialize();
	playerBollWt_.scale_ = {0.5f, 0.5f, 0.5f};
	playerBollWt_.translation_ = position;
	playerBollWt_.TransferMatrix();
	playerBollWt_.UpdateMatrix();
}

KamataEngine::Vector3 PlayerBullet::GetPosition() { return playerBollWt_.translation_; }

void PlayerBullet::Update() { 
	//移動
	playerBollWt_.translation_.x += direction_.x * speed_;
	playerBollWt_.translation_.y += direction_.y * speed_;

	playerBollWt_.TransferMatrix();
	playerBollWt_.UpdateMatrix();
}

void PlayerBullet::Draw() { playerBollModel_->Draw(playerBollWt_, *camera_); }
