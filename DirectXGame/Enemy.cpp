#include "Enemy.h"
using namespace KamataEngine;

Enemy::~Enemy() {}

void Enemy::Initialize() {

	// 画像
	enemyHd = TextureManager::Load("enemy/enemy.png");

	sprite_ = Sprite::Create(enemyHd, enemyPosition);

	bulletHd = TextureManager::Load("enemy/bullet.png");
	spriteBullet_ = Sprite::Create(bulletHd, bulletPosition);


}

KamataEngine::Vector2 Enemy::GetPosition() { return bulletPosition; }

KamataEngine::Vector2 Enemy::GetSize() { return size_; }

void Enemy::Move() {

	if (enemyPosition.x > targetEnemy_.x) {
		enemyPosition.x -= enemySpeed_;
	}

	// 目標地点を通り過ぎないようにする
	if (enemyPosition.x < targetEnemy_.x) {
		enemyPosition.x = targetEnemy_.x;
	}

	sprite_->SetPosition(enemyPosition);

}

void Enemy::Bullet() {
	enemyTimer_ += 1.0f / 60.0f;

	// 3秒経ったら弾を発射
	if (enemyTimer_ >= 10.0f && !isTimer_) {
		bulletPosition = enemyPosition;

		isTimer_ = true;

		// 次の攻撃を複数弾にする
		isSecondAttack_ = true;
	}

	// 弾を左に移動
	if (isTimer_) {
		bulletPosition.x -= bulletSpeed_;

		// 画面左端まで行ったら消す
		if (bulletPosition.x < 0.0f) {
			isTimer_ = false;
			// ここで10秒待つ
			enemyTimer_ = 0.0f;
		}
	}
}

void Enemy::Second() {

}


void Enemy::Update() {
	Move();
	Bullet();
	Second();
}

void Enemy::Draw() {

	Sprite::PreDraw();
	// 描画
	if (isTimer_) {
		spriteBullet_->SetPosition(bulletPosition);
		spriteBullet_->Draw();
	}
	sprite_->Draw();
	Sprite::PostDraw();
}
