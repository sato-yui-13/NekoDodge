#include "Enemy.h"
using namespace KamataEngine;

Enemy::~Enemy() {}

void Enemy::Initialize() {

	// 画像
	enemyHd = TextureManager::Load("enemy/enemy.png");

	sprite_ = Sprite::Create(enemyHd, enemyPosition);

	bulletHd = TextureManager::Load("enemy/bullet.png");
	for (int i = 0; i < 3; i++) {
		spriteBullet[i] = Sprite::Create(bulletHd, bulletPosition[i]);
	}
}

KamataEngine::Vector2 Enemy::GetPosition() { return bulletPosition[0]; }

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

	// 最初の単発攻撃
	if (enemyTimer_ >= 5.0f && isFirstAttack_ && !isTimer_) {

		bulletPosition[0] = enemyPosition;

		isTimer_ = true;
		isBulletActive_ = true;
	}

	// 単発弾移動
	if (isTimer_ && isFirstAttack_) {

		bulletPosition[0].y += bulletSpeed_;

		if (bulletPosition[0].y > 720.0f) {

			isTimer_ = false;
			isBulletActive_ = false; // ←描画停止

			isFirstAttack_ = false;
			isSecondAttack_ = true;

			enemyTimer_ = 0.0f;
		}
	}
}

void Enemy::Second() {
	enemyTimer_ += 1.0f / 60.0f;

	if (isSecondAttack_) {

		if (enemyTimer_ >= 5.0f && isSecondAttack_ && !isTimer_) {

			// 初期位置
			bulletPosition[0] = enemyPosition;

			bulletPosition[1] = {enemyPosition.x - 50.0f, enemyPosition.y};

			bulletPosition[2] = {enemyPosition.x + 50.0f, enemyPosition.y};

			// isSecondAttack_ = false;

			isTimer_ = true;

			isBulletActive_ = true; // ←追加
		}
	}

	// 3方向弾移動
	if (isTimer_) {

		for (int i = 0; i < 3; i++) {

			// bulletPosition[i].x += bulletVelocity[i].x;
			bulletPosition[i].y += enemySpeed_;

			if (bulletPosition[i].y > 720.0f) {

				isTimer_ = false;
				isSecondAttack_ = false; // ←描画停止

				// 三回個目のflag
				isThirdAttack_ = true;

				enemyTimer_ = 0.0f;
			}
		}
	}
}

void Enemy::Third() {
	enemyTimer_ += 1.0f / 60.0f;

	// 扇状弾の生成は1回だけ
	if (isThirdAttack_) {
		if (enemyTimer_ >= 5.0f && isThirdAttack_ && !isTimer_) {

			bulletPosition[0] = {enemyPosition.x - 100.0f, enemyPosition.y};
			bulletPosition[1] = {enemyPosition.x, enemyPosition.y};
			bulletPosition[2] = {enemyPosition.x + 100.0f, enemyPosition.y};

			bulletVelocity[0] = {-3.0f, 5.0f};
			bulletVelocity[1] = {0.0f, 5.0f};
			bulletVelocity[2] = {3.0f, 5.0f};

			isThirdAttack_ = false;

			isTimer_ = true;
			isBulletActive_ = true;
		}
	}

	// 移動
	if (isTimer_) {

		for (int i = 0; i < 3; i++) {

			 bulletPosition[i].x += bulletVelocity[i].x;
			bulletPosition[i].y += bulletVelocity[i].y;

			if (bulletPosition[i].y > 720.0f) {

				isTimer_ = false;
				isThirdAttack_ = false; // ←描画停止

				enemyTimer_ = 0.0f;
			}
		}
	}
}

void Enemy::Fourth() {
	if (!isSplitActive_) {

		// 最初の1発
		bulletPosition[0] = enemyPosition;

		bulletVelocity[0] = {0.0f, 5.0f};

		isSplitActive_ = true;
		isTimer_ = true;
	}

	// 親弾移動
	if (isTimer_) {

		bulletPosition[0].x += bulletVelocity[0].x;
		bulletPosition[0].y += bulletVelocity[0].y;

		splitTimer_ += 1.0f / 60.0f;

		// 2秒後に分裂
		if (splitTimer_ >= 2.0f) {

			// 左右に分裂
			bulletPosition[1] = bulletPosition[0];
			bulletPosition[2] = bulletPosition[0];

			bulletVelocity[1] = {-3.0f, 5.0f};
			bulletVelocity[2] = {3.0f, 5.0f};

			isSplit_ = true;
		}
	}

	// 分裂後
	if (isSplit_) {

		for (int i = 1; i < 3; i++) {

			bulletPosition[i].x += bulletVelocity[i].x;
			bulletPosition[i].y += bulletVelocity[i].y;
		}
	}

}

void Enemy::Update() {
	Move();
	Bullet();

	if (isSecondAttack_) {
		Second();
	}
	
		Third();
	
}
void Enemy::Draw() {
	Sprite::PreDraw();

	if (isBulletActive_) {

		// 単発
		if (isFirstAttack_) {

			spriteBullet[0]->SetPosition(bulletPosition[0]);
			spriteBullet[0]->Draw();

		}
		// 3発系
		else {

			for (int i = 0; i < 3; i++) {

				spriteBullet[i]->SetPosition(bulletPosition[i]);
				spriteBullet[i]->Draw();
			}
		}
	}

	// 敵
	sprite_->Draw();

	Sprite::PostDraw();
}
