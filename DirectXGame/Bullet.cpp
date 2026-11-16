#include "Bullet.h"
#include "player.h"
#include <Windows.h>
#include <cmath>
#include <string>
using namespace KamataEngine;

Bullet::~Bullet() {}

void Bullet::Initialize(
    KamataEngine::WorldTransform* target, KamataEngine::Vector3 position, KamataEngine::Model* ballModel, KamataEngine::Camera* camera, player* player, float speed_, Bullet::MoveType moveType,
    KamataEngine::Vector2 direction) {
	player_ = player;
	target_ = target;
	camera_ = camera;
	ballModel_ = ballModel;

	direction_ = direction;
	moveType_ = moveType;
	bulletWt_.Initialize();
	bulletWt_.translation_ = position;
	bulletWt_.scale_ = {0.5f, 0.5f, 0.5f};
	bulletWt_.TransferMatrix();
	bulletWt_.UpdateMatrix();
	speed = speed_;
}

void Bullet::Homing() {

	waveTime_ += 1.0f / 60.0f;

	// 位置取得
	targetPosition_.x = target_->translation_.x;
	targetPosition_.y = target_->translation_.y;

	// プレイヤーと弾の方向
	velocity_.x = targetPosition_.x - bulletWt_.translation_.x;
	velocity_.y = targetPosition_.y - bulletWt_.translation_.y;

	// 長さ求めてる
	float length = std::sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y);

	if (length > 0) {
		velocity_.x /= length;
		velocity_.y /= length;
	}

	float sideX = -velocity_.y;
	float sideY = velocity_.x;

	float wave = std::sin(waveTime_ * 3.0f) * 0.15f;

	// 更新
	bulletWt_.translation_.x += speed * (velocity_.x + sideX * wave);
	bulletWt_.translation_.y += speed * (velocity_.y + sideY * wave);
}

void Bullet::SetPosition(KamataEngine::Vector3 position) {
	bulletWt_.translation_ = position;
	bulletWt_.UpdateMatrix();
}

void Bullet::StraightMove() {
	// 直線
	bulletWt_.translation_.x += direction_.x * speed;
	bulletWt_.translation_.y += direction_.y * speed;
}

bool Bullet::CheckCollision() {

	float dx = bulletWt_.translation_.x - target_->translation_.x;
	float dy = bulletWt_.translation_.y - target_->translation_.y;

	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance <= 1.0f) {
		return true;
	}

	return false;
}

void Bullet::Update() {

	if (moveType_ == MoveType::Homing) {
		// 追尾処理
		Homing();
	} else if (moveType_ == MoveType::Straight) {
		// 直線移動処理

		StraightMove();
	}

	if (!isHit_ && CheckCollision()) {
		player_->TakeDamage();
		OutputDebugStringA("Hit!\n");
		isHit_ = true;
	}

	bulletWt_.UpdateMatrix();
}

void Bullet::Draw() { ballModel_->Draw(bulletWt_, *camera_); }
