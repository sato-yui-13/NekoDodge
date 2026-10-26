#include "Enemy.h"
#include <Windows.h>
#include <cmath>
#include <string>

using namespace KamataEngine;

Enemy::~Enemy() {
	for (Bullet* bullet : bullets_) {
		delete bullet;
	}
	bullets_.clear();

	delete bollModel_;
	bollModel_ = nullptr;
}
void Enemy::Initialize(KamataEngine::Model* enemyModel, KamataEngine::WorldTransform* target, KamataEngine::Camera* camera, player* player) {
	player_ = player;
	camera_ = camera;
	target_= target;
	// 敵
	enemyModel_ = enemyModel;
	enemyWt_.Initialize();
	enemyWt_.translation_ = {-10.0f, 2.0f, 0.0f};
	enemyWt_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWt_.TransferMatrix();
	enemyWt_.UpdateMatrix();


	bollModel_ = Model::CreateFromOBJ("boll", true);
	for (int i = 0; i < 2; i++) {
		Bullet* bullet = new Bullet();

		Vector3 bulletPosition = enemyWt_.translation_;
		bulletPosition.x += (i == 0) ? -0.25f : 0.25f;

		bullet->Initialize(target_, bulletPosition, bollModel_, camera_, player_);
		bullets_.push_back(bullet);
	}


}

void Enemy::UpdateEntrance() {
	enemyWt_.translation_.x += speed_;

	if (enemyWt_.translation_.x > -2.0f) {
		speed_ = 0.0f;
		isEntranceFinished_ = true;

		for (int i = 0; i < bullets_.size(); i++) {
			Vector3 bulletPosition = enemyWt_.translation_;
			bulletPosition.x += (i == 0) ? -0.25f : 0.25f;
			bullets_[i]->SetPosition(bulletPosition);
		}

	}

	enemyWt_.UpdateMatrix();
}

// 敵の移動
void Enemy::Move() {}

void Enemy::Update() {
	Move();

	enemyWt_.UpdateMatrix();

	for (Bullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw() {
	enemyModel_->Draw(enemyWt_, *camera_);

	for (Bullet* bullet : bullets_) {
		bullet->Draw();
	}
}