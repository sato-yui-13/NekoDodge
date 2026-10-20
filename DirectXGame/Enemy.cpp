#include "Enemy.h"
#include <string>
#include <Windows.h>
#include <cmath>


using namespace KamataEngine;

Enemy::~Enemy() {}

void Enemy::Initialize(KamataEngine::Model* enemyModel, KamataEngine::Model* ballModel, KamataEngine::Camera* camera) {

	camera_=camera;
	

	//敵
	enemyModel_= enemyModel;
	enemyWt_.Initialize();
	enemyWt_.translation_ = {0.0f, 0.0f, 0.0f};
	enemyWt_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWt_.TransferMatrix();

	//攻撃
	ballModel_ = ballModel;
	ballWt_.Initialize();
	ballWt_.translation_ = {0.0f, 0.0f, 0.0f};
	ballWt_.scale_ = {0.5f, 0.5f, 0.5f};
	ballWt_.TransferMatrix();

	
}

// 敵の移動
void Enemy::Move() {


}

void Enemy::Update() {

	
}

void Enemy::Draw() {

	//enemyModel_->Draw(enemyWt_, *camera_);
	//

	//if (!isLaunched_) {
	//	ballModel_->Draw(ballWt_, *camera_);
	//}
	

	
}


