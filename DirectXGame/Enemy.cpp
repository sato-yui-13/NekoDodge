
#include "Enemy.h"
#include <cassert>
#include <cmath>

using namespace KamataEngine;

namespace {
constexpr float kScreenWidth = 1280.0f;
constexpr float kScreenHeight = 720.0f;
constexpr float kDeltaTime = 1.0f / 60.0f;
constexpr float kSpawnInterval = 0.2f;
constexpr float kBulletZ = 0.0f;

// 画面座標から3D座標への変換。
// カメラの投影方式・画角に合わせて調整すること。
constexpr float kWorldScale = 0.0064f;

Vector3 ScreenToWorld(Vector2 position) { return {(position.x - kScreenWidth * 0.5f) * kWorldScale, (kScreenHeight * 0.5f - position.y) * kWorldScale, kBulletZ}; }
} // namespace

Enemy::~Enemy() = default;

//==================================================
// 初期化
//==================================================

void Enemy::Initialize(Model* enemyModel, Model* bulletModel, Camera* camera, Vector2 position) {

	assert(enemyModel);
	assert(bulletModel);
	assert(camera);

	enemyModel_ = enemyModel;
	bulletModel_ = bulletModel;
	camera_ = camera;

	enemyPosition_ = position;
	enemyVisible_ = true;

	enemyWt_.Initialize();

	for (int i = 0; i < 8; i++) {
		bulletWt_[i].Initialize();
		bulletWt_[i].scale_ = {0.2f, 0.2f, 0.2f};

		bulletActive_[i] = false;
		bulletPosition[i] = {-1000.0f, -1000.0f};
		bulletVelocity[i] = {};
	}

	std::uniform_int_distribution<int> attackDist(1, 5);
	attackType_ = attackDist(randomEngine_);

	enemyTimer_ = 0.0f;
	bulletSpawnTimer_ = 0.0f;
	enemyMoveTimer_ = 0.0f;

	attackStarted_ = false;
	isEnemyMoving_ = false;
	isSplit_ = false;

	SyncTransforms();
}

//==================================================
// 画面座標から3Dモデル座標へ反映
//==================================================

void Enemy::SyncTransforms() {

	enemyWt_.translation_ = ScreenToWorld(enemyPosition_);
	enemyWt_.UpdateMatrix();

	for (int i = 0; i < 8; i++) {
		bulletWt_[i].translation_ = ScreenToWorld(bulletPosition[i]);
		bulletWt_[i].UpdateMatrix();
	}
}

//==================================================
// 取得
//==================================================

Vector2 Enemy::GetBulletPosition(int index) {

	if (index < 0 || index >= 8 || !bulletActive_[index]) {
		return {-1000.0f, -1000.0f};
	}

	return bulletPosition[index];
}

Vector2 Enemy::GetSize() { return size_; }

int Enemy::GetBulletCount() {

	int count = 0;

	for (int i = 0; i < 8; i++) {
		if (bulletActive_[i]) {
			count++;
		}
	}

	return count;
}

//==================================================
// 敵の移動
//==================================================

void Enemy::Move() {

	if (!isEnemyMoving_) {
		return;
	}

	enemyMoveTimer_ += kDeltaTime;

	if (enemyMoveTimer_ >= 0.5f) {
		enemyPosition_ = nextEnemyPosition_;

		isEnemyMoving_ = false;
		enemyVisible_ = true;
		enemyMoveTimer_ = 0.0f;
	}
}

//==================================================
// 次の攻撃の準備
//==================================================

void Enemy::PrepareNextAttack() {

	attackStarted_ = false;
	enemyTimer_ = 0.0f;
	bulletSpawnTimer_ = 0.0f;
	bulletsSpawned_ = 0;
	bulletsToSpawn_ = 0;
	isSplit_ = false;
	splitTimer_ = 0.0f;

	for (int i = 0; i < 8; i++) {
		bulletActive_[i] = false;
		bulletPosition[i] = {-1000.0f, -1000.0f};
	}

	std::uniform_real_distribution<float> xDist(100.0f, 1180.0f);
	std::uniform_real_distribution<float> yDist(100.0f, 300.0f);
	std::uniform_int_distribution<int> attackDist(1, 5);

	nextEnemyPosition_ = {xDist(randomEngine_), yDist(randomEngine_)};

	attackType_ = attackDist(randomEngine_);

	// 攻撃終了後は敵を一度隠して移動
	enemyPosition_ = {-1000.0f, -1000.0f};
	enemyVisible_ = false;
	isEnemyMoving_ = true;
	enemyMoveTimer_ = 0.0f;
}

//==================================================
// 攻撃開始
//==================================================

void Enemy::StartAttack() {

	attackStarted_ = true;
	bulletsSpawned_ = 0;
	bulletSpawnTimer_ = 0.0f;

	switch (attackType_) {
	case 1:
		bulletsToSpawn_ = 1;
		break;

	case 2:
	case 3:
	case 4:
		bulletsToSpawn_ = 3;
		break;

	case 5:
		bulletsToSpawn_ = 8;
		break;
	}
}

//==================================================
// 次の弾を1発発射
//==================================================

void Enemy::SpawnNextBullet() {

	int i = bulletsSpawned_;

	bulletPosition[i] = enemyPosition_;

	switch (attackType_) {

	// 単発
	case 1:
		bulletVelocity[i] = {0.0f, bulletSpeed_};
		break;

	// 3方向。左右の位置をずらして順番に発射
	case 2:
		bulletPosition[i].x += (i - 1) * 50.0f;
		bulletVelocity[i] = {0.0f, enemySpeed_};
		break;

	// 扇型。1発ごとに方向を変える
	case 3:
		bulletPosition[i].x += (i - 1) * 100.0f;
		bulletVelocity[i] = {(i - 1) * 3.0f, enemySpeed_};
		break;

	// 分裂。親弾を発射し、後から左右へ分裂
	case 4:
		if (i == 0) {
			bulletVelocity[i] = {0.0f, enemySpeed_};
			splitTimer_ = 0.0f;
			isSplit_ = false;
		}
		break;

	// 8方向。各方向を順番に発射
	case 5: {
		const float angle = 2.0f * 3.14159265f * static_cast<float>(i) / 8.0f;

		bulletVelocity[i] = {cosf(angle) * bulletSpeed_, sinf(angle) * bulletSpeed_};
		break;
	}
	}

	bulletActive_[i] = true;
	bulletsSpawned_++;
}

//==================================================
// 攻撃更新
//==================================================

void Enemy::UpdateAttack() {

	enemyTimer_ += kDeltaTime;

	// 攻撃開始まで待機
	const float waitTime = (attackType_ == 5) ? 5.0f : 2.0f;

	if (!attackStarted_ && enemyTimer_ >= waitTime) {
		StartAttack();
	}

	if (!attackStarted_) {
		return;
	}

	// 一定時間ごとに1発だけ発射
	bulletSpawnTimer_ += kDeltaTime;

	if (bulletsSpawned_ < bulletsToSpawn_ && bulletSpawnTimer_ >= kSpawnInterval) {

		SpawnNextBullet();
		bulletSpawnTimer_ = 0.0f;
	}

	// 分裂攻撃：親弾が発射されてから0.5秒後に左右へ分裂
	if (attackType_ == 4 && bulletsSpawned_ >= 1 && bulletActive_[0] && !isSplit_) {

		splitTimer_ += kDeltaTime;

		if (splitTimer_ >= 0.5f) {
			bulletPosition[1] = bulletPosition[0];
			bulletPosition[2] = bulletPosition[0];

			bulletVelocity[1] = {-3.0f, enemySpeed_};
			bulletVelocity[2] = {3.0f, enemySpeed_};

			bulletActive_[1] = true;
			bulletActive_[2] = true;

			// 分裂後の弾も発射済みとして扱う
			bulletsSpawned_ = 3;
			isSplit_ = true;
		}
	}

	bool anyBulletAlive = false;

	for (int i = 0; i < bulletsSpawned_; i++) {

		if (!bulletActive_[i]) {
			continue;
		}

		bulletPosition[i].x += bulletVelocity[i].x;
		bulletPosition[i].y += bulletVelocity[i].y;

		const bool outside = bulletPosition[i].x < 0.0f || bulletPosition[i].x > kScreenWidth || bulletPosition[i].y < 0.0f || bulletPosition[i].y > kScreenHeight;

		if (outside) {
			bulletActive_[i] = false;
			bulletPosition[i] = {-1000.0f, -1000.0f};
		} else {
			anyBulletAlive = true;
		}
	}

	// 全弾の発射が終わり、生きている弾がなくなったら次へ
	if (bulletsSpawned_ >= bulletsToSpawn_ && !anyBulletAlive) {

		PrepareNextAttack();
	}
}

//==================================================
// Update
//==================================================

void Enemy::Update() {

	if (isEnemyMoving_) {
		Move();
	} else {
		UpdateAttack();
	}

	SyncTransforms();
}

//==================================================
// Draw：3Dモデルのみ
//==================================================

void Enemy::Draw() {

	if (enemyVisible_) {
		enemyModel_->Draw(enemyWt_, *camera_);
	}

	for (int i = 0; i < 8; i++) {

		if (bulletActive_[i]) {
			bulletModel_->Draw(bulletWt_[i], *camera_);
		}
	}
}
