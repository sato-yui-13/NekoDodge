#include "Enemy.h"
#include <Windows.h>
#include <cmath>
#include <string>

using namespace KamataEngine;

Enemy::~Enemy() {}

void Enemy::Initialize(KamataEngine::Model* enemyModel, KamataEngine::Model* ballModel, KamataEngine::Camera* camera) {

	camera_ = camera;

	// 敵
	enemyModel_ = enemyModel;
	enemyWt_.Initialize();
	enemyWt_.translation_ = {-10.0f, 2.0f, 0.0f};
	enemyWt_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWt_.TransferMatrix();
	enemyWt_.UpdateMatrix();

	// 攻撃
	ballModel_ = ballModel;
	ballWt_.Initialize();
	ballWt_.translation_ = {0.0f, 0.0f, 0.0f};
	ballWt_.scale_ = {0.5f, 0.5f, 0.5f};

	ballWt_.UpdateMatrix();
}

void Enemy::UpdateEntrance() {
	//敵の入場
	enemyWt_.translation_.x += speed_;
	if (enemyWt_.translation_.x > -2.0f) {
		speed_ = 0.0f;
	}
	enemyWt_.UpdateMatrix();

}

// 敵の移動
void Enemy::Move() {
	
}

void Enemy::Update() {
	Move();
	enemyWt_.UpdateMatrix();
}

void Enemy::Draw() {

	enemyModel_->Draw(enemyWt_, *camera_);

	if (!isLaunched_) {
	//	ballModel_->Draw(ballWt_, *camera_);
	}
}


