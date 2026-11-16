#include "Enemy.h"
#include <Windows.h>
#include <algorithm>
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

void Enemy::Initialize(KamataEngine::Model* enemyModel, KamataEngine::WorldTransform* target, KamataEngine::Camera* camera, player* player, KamataEngine::Vector3 position, bool isFirstEnemy) {
	player_ = player;
	camera_ = camera;
	target_ = target;
	isFirstEnemy_ = isFirstEnemy;
	// 敵
	enemyModel_ = enemyModel;
	enemyWt_.Initialize();
	enemyWt_.translation_ = {position.x, position.y, position.z};
	//方向処理
	entranceDirection_.x = -position.x;
	entranceDirection_.y = -position.y;

	float length = sqrtf(entranceDirection_.x * entranceDirection_.x + entranceDirection_.y * entranceDirection_.y);
	entranceDirection_.x /= length;
	entranceDirection_.y /= length;

	enemyWt_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWt_.TransferMatrix();
	enemyWt_.UpdateMatrix();

	bollModel_ = Model::CreateFromOBJ("boll", true);
}

void Enemy::FireBullet() {
	Bullet* bullet = new Bullet();
	float bulletSpeed = isRapidFire_ ? 0.08f : 0.05f;
	Vector3 bulletPosition = enemyWt_.translation_;

	bullet->Initialize(target_, bulletPosition, bollModel_, camera_, player_, bulletSpeed, Bullet::MoveType::Homing, Vector2{0.0f, 0.0f});

	bullets_.push_back(bullet);
}

void Enemy::FireFanBullet() {

	float dx = target_->translation_.x - enemyWt_.translation_.x;
	float dy = target_->translation_.y - enemyWt_.translation_.y;

	// 長さ求めてる
	float length = std::sqrt(dx * dx + dy * dy);

	if (length > 0) {
		dx /= length;
		dy /= length;
	}

	// 角度
	float angle = std::atan2(dy, dx);

	// 15℃
	for (int i = 0; i < 5; i++) {
		float offset = (i - 2) * 15.0f * 3.14159265f / 180.0f;
		float bulletAngle = angle + offset;

		Vector2 direction;
		direction.x = std::cos(bulletAngle);
		direction.y = std::sin(bulletAngle);

		 Bullet* bullet = new Bullet();
		 Vector3 bulletPosition = enemyWt_.translation_;
		 bullet->Initialize(target_, bulletPosition, bollModel_, camera_, player_, 0.08f, Bullet::MoveType::Straight, direction);
		 bullets_.push_back(bullet);
	
	}
}

void Enemy::UpdateEntrance() {
	


	if (isFirstEnemy_) {
		// 1体目の入場処理
		enemyWt_.translation_.x += speed_;
		if (enemyWt_.translation_.x > -2.0f) {
			speed_ = 0.0f;
			isEntranceFinished_ = true;
		}
	} else {
		// 2体目以降の入場処理
		enemyWt_.translation_.x += entranceDirection_.x * speed_;
		enemyWt_.translation_.y += entranceDirection_.y * speed_;

		float distance = sqrtf(enemyWt_.translation_.x * enemyWt_.translation_.x + enemyWt_.translation_.y * enemyWt_.translation_.y);

		if (distance < 2.0f) {
			isEntranceFinished_ = true;
		}
	}

	enemyWt_.UpdateMatrix();

}

// 敵の移動
void Enemy::Move() {}

void Enemy::TakeDamage() { isDead_ = true; }

void Enemy::CheckCollision(PlayerBullet* playerBullet) {
	KamataEngine::Vector3 enemyPosition = enemyWt_.translation_;
	KamataEngine::Vector3 bulletPosition = playerBullet->GetPosition();
	float diffX = enemyPosition.x - bulletPosition.x;
	float diffY = enemyPosition.y - bulletPosition.y;
	float diffZ = enemyPosition.z - bulletPosition.z;

	float distance = std::sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);

	if (distance <= 1.0f) {
		isDead_ = true;
	}
}

void Enemy::Update() {
	Move();

	attackTimer_ += 1.0f / 60.0f;

	if (attackType_ == AttackType::Homing){

		int maxShots = isRapidFire_ ? 5 : maxShotCount_;

		float attackInterval = isRapidFire_ ? 0.1f : 0.3f;

		if (isResting_) {
			if (attackTimer_ >= 1.0f) {
				isResting_ = false;
				shotCount_ = 0;
				attackTimer_ = 0.0f;
			}
		} else {
			if (shotCount_ < maxShots && attackTimer_ >= attackInterval) {
				FireBullet();
				shotCount_++;
				attackTimer_ = 0.0f;
			}

			if (shotCount_ >= maxShots) {
				isResting_ = true;
				attackTimer_ = 0.0f;
			}
		}

		

		
	
	
	} else if (attackType_ == AttackType::Fan) {
		fanAttackTimer_ += 1.0f / 60.0f;
		if (fanAttackTimer_ > 1.0f) {
			FireFanBullet();
			fanAttackTimer_ = 0.0f;
		}
	}



	for (Bullet* bullet : bullets_) {
		bullet->Update();
		// bullet->IsHit();
	}

	bullets_.erase(
	    std::remove_if(
	        bullets_.begin(), bullets_.end(),
	        [](Bullet* bullet) {
		        if (bullet->IsHit()) {
			        delete bullet;
			        return true;
		        }
		        return false;
	        }),
	    bullets_.end());
	enemyWt_.UpdateMatrix();


}

void Enemy::Draw() {
	enemyModel_->Draw(enemyWt_, *camera_);

	for (Bullet* bullet : bullets_) {
		bullet->Draw();
	}
}
