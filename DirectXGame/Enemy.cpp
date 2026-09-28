#include "Enemy.h"
#include <cmath>
#include <random>

using namespace KamataEngine;

Enemy::~Enemy() {}

void Enemy::Initialize(Vector2 position) {

	enemyPosition = position;

	// 攻撃を1～5からランダム
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> attackDist(1, 5);

	attackType_ = attackDist(gen);

	// 画像
	enemyHd = TextureManager::Load("enemy/enemy.png");

	sprite_ = Sprite::Create(enemyHd, enemyPosition);

	bulletHd = TextureManager::Load("enemy/bullet.png");

	for (int i = 0; i < 8; i++) {
		spriteBullet[i] = Sprite::Create(bulletHd, bulletPosition[i]);
	}
}

// 敵自身の位置を返す
KamataEngine::Vector2 Enemy::GetBulletPosition(int index) { return bulletPosition[index]; }

KamataEngine::Vector2 Enemy::GetSize() { return size_; }

// 敵の移動
void Enemy::Move() {

	if (!isEnemyMoving_) {
		return;
	}

	enemyMoveTimer_ += 1.0f / 60.0f;

	// 0.5秒後に新しい場所へ移動
	if (enemyMoveTimer_ >= 0.5f) {

		enemyPosition = nextEnemyPosition_;

		sprite_->SetPosition(enemyPosition);

		isEnemyMoving_ = false;

		enemyMoveTimer_ = 0.0f;
	}
}

//==================================================
// 1回目　単発
//==================================================

void Enemy::Bullet() {

	enemyTimer_ += 2.0f / 60.0f;

	// 単発攻撃開始
	if (enemyTimer_ >= 2.0f && !isTimer_) {

		bulletPosition[0] = enemyPosition;

		isTimer_ = true;
		isBulletActive_ = true;
	}

	// 単発弾移動
	if (isTimer_) {

		bulletPosition[0].y += bulletSpeed_;

		// 弾が画面外
		if (bulletPosition[0].y > 720.0f) {

			isTimer_ = false;
			isBulletActive_ = false;

			enemyTimer_ = 0.0f;

			// 敵を消す
			sprite_->SetPosition({-1000.0f, -1000.0f});

			// 次の敵位置をランダム決定
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
			std::uniform_real_distribution<float> yDist(100.0f, 300.0f);

			nextEnemyPosition_ = {xDist(gen), yDist(gen)};

			// 移動開始
			isEnemyMoving_ = true;

			// 次の攻撃をランダム
			std::uniform_int_distribution<int> attackDist(1, 5);
			attackType_ = attackDist(gen);
		}
	}
}

//==================================================
// 2回目　3方向
//==================================================

void Enemy::Second() {

	enemyTimer_ += 1.0f / 60.0f;

	// 3方向弾開始
	if (enemyTimer_ >= 2.0f && !isTimer_) {

		bulletPosition[0] = enemyPosition;

		bulletPosition[1] = {enemyPosition.x - 50.0f, enemyPosition.y};

		bulletPosition[2] = {enemyPosition.x + 50.0f, enemyPosition.y};

		isTimer_ = true;
		isBulletActive_ = true;
	}

	// 3方向弾移動
	if (isTimer_) {

		allOut = true;

		for (int i = 0; i < 3; i++) {

			bulletPosition[i].y += enemySpeed_;

			// 1個でも画面内ならまだ終了しない
			if (bulletPosition[i].y <= 720.0f) {
				allOut = false;
			}
		}

		// 3発全部画面外
		if (allOut) {

			isTimer_ = false;
			isBulletActive_ = false;

			allOut = false;

			enemyTimer_ = 0.0f;

			// 敵を消す
			sprite_->SetPosition({-1000.0f, -1000.0f});

			// 次の位置をランダム
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
			std::uniform_real_distribution<float> yDist(100.0f, 300.0f);

			nextEnemyPosition_ = {xDist(gen), yDist(gen)};

			isEnemyMoving_ = true;

			// 次の攻撃
			std::uniform_int_distribution<int> attackDist(1, 5);
			attackType_ = attackDist(gen);
		}
	}
}

//==================================================
// 3回目　扇型
//==================================================

void Enemy::Third() {

	enemyTimer_ += 1.0f / 60.0f;

	// 扇型弾の生成
	if (enemyTimer_ >= 2.0f && !isTimer_) {

		bulletPosition[0] = {enemyPosition.x - 100.0f, enemyPosition.y};

		bulletPosition[1] = enemyPosition;

		bulletPosition[2] = {enemyPosition.x + 100.0f, enemyPosition.y};

		bulletVelocity[0] = {-3.0f, 5.0f};
		bulletVelocity[1] = {0.0f, 5.0f};
		bulletVelocity[2] = {3.0f, 5.0f};

		isTimer_ = true;
		isBulletActive_ = true;
	}

	// 弾移動
	if (isTimer_) {

		allOut = true;

		for (int i = 0; i < 3; i++) {

			bulletPosition[i].x += bulletVelocity[i].x;
			bulletPosition[i].y += bulletVelocity[i].y;

			// 1個でも画面内なら終了しない
			if (bulletPosition[i].y <= 720.0f) {
				allOut = false;
			}
		}

		// 3発全部画面外
		if (allOut) {

			isTimer_ = false;
			isBulletActive_ = false;

			allOut = false;

			enemyTimer_ = 0.0f;

			OutputDebugStringA("Third End!\n");

			// 敵を消す
			sprite_->SetPosition({-1000.0f, -1000.0f});

			// 次の位置をランダム
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
			std::uniform_real_distribution<float> yDist(100.0f, 300.0f);

			nextEnemyPosition_ = {xDist(gen), yDist(gen)};

			isEnemyMoving_ = true;

			// 次の攻撃
			std::uniform_int_distribution<int> attackDist(1, 5);
			attackType_ = attackDist(gen);
		}
	}
}

//==================================================
// 4回目　分裂
//==================================================

void Enemy::Fourth() {

	enemyTimer_ += 1.0f / 60.0f;

	// 4回目開始
	if (enemyTimer_ >= 2.0f && !isTimer_) {

		bulletPosition[0] = enemyPosition;

		bulletVelocity[0] = {0.0f, 5.0f};

		OutputDebugStringA("Fourth Start!\n");

		isSplitActive_ = true;

		isTimer_ = true;
		isBulletActive_ = true;

		isSplit_ = false;

		splitTimer_ = 0.0f;
	}

	// 親弾
	if (isSplitActive_) {

		bulletPosition[0].x += bulletVelocity[0].x;
		bulletPosition[0].y += bulletVelocity[0].y;

		splitTimer_ += 1.0f / 60.0f;

		// 分裂
		if (splitTimer_ >= 0.5f && !isSplit_) {

			OutputDebugStringA("SPLIT!\n");

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

		// 3発全部画面外
		if (bulletPosition[0].y > 720.0f && bulletPosition[1].y > 720.0f && bulletPosition[2].y > 720.0f) {

			isSplitActive_ = false;
			isSplit_ = false;

			isTimer_ = false;
			isBulletActive_ = false;

			enemyTimer_ = 0.0f;

			// 敵を消す
			sprite_->SetPosition({-1000.0f, -1000.0f});

			// 次の位置をランダム
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
			std::uniform_real_distribution<float> yDist(100.0f, 300.0f);

			nextEnemyPosition_ = {xDist(gen), yDist(gen)};

			isEnemyMoving_ = true;

			// 次の攻撃
			std::uniform_int_distribution<int> attackDist(1, 5);
			attackType_ = attackDist(gen);
		}
	}
}

//==================================================
// 5回目　8方向
//==================================================

void Enemy::Eight() {

	enemyTimer_ += 1.0f / 60.0f;

	// 8方向弾を発射
	if (enemyTimer_ >= 5.0f && !isTimer_) {

		for (int i = 0; i < 8; i++) {

			bulletPosition[i] = enemyPosition;

			float angle = 3.141592f * 2.0f * i / 8.0f;

			bulletVelocity[i].x = cosf(angle) * 5.0f;

			bulletVelocity[i].y = sinf(angle) * 5.0f;
		}

		isTimer_ = true;
		isBulletActive_ = true;
	}

	// 弾を移動
	if (isTimer_) {

		// 最初は全部画面外
		allOut = true;

		for (int i = 0; i < 8; i++) {

			bulletPosition[i].x += bulletVelocity[i].x;
			bulletPosition[i].y += bulletVelocity[i].y;

			// 1個でも画面内ならfalse
			if (bulletPosition[i].x >= 0.0f && bulletPosition[i].x <= 1280.0f && bulletPosition[i].y >= 0.0f && bulletPosition[i].y <= 720.0f) {

				allOut = false;
			}
		}

		// 8個全部画面外
		if (allOut) {

			isTimer_ = false;
			isBulletActive_ = false;

			allOut = false;

			enemyTimer_ = 0.0f;

			// 敵を消す
			sprite_->SetPosition({-1000.0f, -1000.0f});

			// 次の位置をランダム
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
			std::uniform_real_distribution<float> yDist(100.0f, 300.0f);

			nextEnemyPosition_ = {xDist(gen), yDist(gen)};

			isEnemyMoving_ = true;

			// 次の攻撃
			std::uniform_int_distribution<int> attackDist(1, 5);
			attackType_ = attackDist(gen);
		}
	}
}

int Enemy::GetBulletCount() {
	if (!isBulletActive_) {
		return 0;
	}

	if (attackType_ == 1) {
		return 1;
	}

	if (attackType_ == 5) {
		return 8;
	}

	return 3;
}

//==================================================
// Update
//==================================================

void Enemy::Update() {

	// 敵が移動中なら攻撃しない
	if (isEnemyMoving_) {

		Move();

		return;
	}

	switch (attackType_) {

	case 1:
		Bullet();
		break;

	case 2:
		Second();
		break;

	case 3:
		Third();
		break;

	case 4:
		Fourth();
		break;

	case 5:
		Eight();
		break;
	}
}

//==================================================
// Draw
//==================================================

void Enemy::Draw() {

	Sprite::PreDraw();

	if (isBulletActive_) {

		// 1：単発
		if (attackType_ == 1) {

			spriteBullet[0]->SetPosition(bulletPosition[0]);

			spriteBullet[0]->Draw();
		}

		// 5：8方向
		else if (attackType_ == 5) {

			for (int i = 0; i < 8; i++) {

				spriteBullet[i]->SetPosition(bulletPosition[i]);

				spriteBullet[i]->Draw();
			}
		}

		// 分裂
		else if (isSplit_) {

			for (int i = 0; i < 3; i++) {

				spriteBullet[i]->SetPosition(bulletPosition[i]);

				spriteBullet[i]->Draw();
			}
		}

		// 2・3
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