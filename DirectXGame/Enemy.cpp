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

void Enemy::Update() {

	enemyTimer_ += 1.0f / 60.0f;

	// 3秒経ったら弾を発射
	if (enemyTimer_ >= 10.0f && !isTimer_) {
		bulletPosition = enemyPosition;
		
		isTimer_ = true;

	} 

	// 弾を左に移動
	if (isTimer_) {
		bulletPosition.x -= enemySpeed_;

		// 画面左端まで行ったら消す
		if (bulletPosition.x < 0.0f) {
			isTimer_ = false;
			// ここで10秒待つ
			enemyTimer_ = 0.0f;
		}
	}
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
