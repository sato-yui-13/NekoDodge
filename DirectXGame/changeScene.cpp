
#include "changeScene.h"
#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace KamataEngine;

changeScene::changeScene() {}

changeScene::~changeScene() {}

void changeScene::Initialize(KamataEngine::Model* squareModel, KamataEngine::Camera* camera) {

	assert(squareModel);
	assert(camera);

	camera_ = camera;
	ballsModel_ = squareModel;

	isStart_ = false;
	isAnimEnd_ = false;
	frame_ = 0;
	landedCount_ = 0;

	for (int i = 0; i < 100; i++) {

		colorful[i].ballsWt_.Initialize();

		// 丸ごとにサイズをランダムにする
		float scale = scaleDist_(gen_);

		colorful[i].ballsWt_.scale_ = {scale, scale, scale};

		// 横の位置をランダムにする
		colorful[i].ballsWt_.translation_.x = xDist_(gen_);

		// 最初の高さをバラバラにする
		colorful[i].ballsWt_.translation_.y = 12.0f + yDist_(gen_);

		colorful[i].ballsWt_.translation_.z = 0.0f;

		// 落下速度
		colorful[i].velocity = {0.0f, -0.2f, 0.0f};

		// 最初はランダムなタイミングで出現
		colorful[i].delay = delayDist_(gen_);

		colorful[i].active = false;
		colorful[i].landed = false;
		colorful[i].targetY = -12.0f;

		colorful[i].ballsWt_.TransferMatrix();
		colorful[i].ballsWt_.UpdateMatrix();
	}
}

bool changeScene::IsCollision(int indexA, int indexB) {

	const auto& a = colorful[indexA];
	const auto& b = colorful[indexB];

	const Vector3& posA = a.ballsWt_.translation_;
	const Vector3& posB = b.ballsWt_.translation_;

	float dx = posA.x - posB.x;
	float dy = posA.y - posB.y;
	float dz = posA.z - posB.z;

	float distanceSquared = dx * dx + dy * dy + dz * dz;

	float radiusA = a.ballsWt_.scale_.x;
	float radiusB = b.ballsWt_.scale_.x;

	float radiusSum = radiusA + radiusB;

	return distanceSquared <= radiusSum * radiusSum;
}

void changeScene::Update() {

	if (!isStart_ || isAnimEnd_) {
		return;
	}

	frame_++;

	// 演出時間が終わったら終了
	if (frame_ >= kMaxAnimationFrames) {
		isAnimEnd_ = true;
		return;
	}

	// 丸を降らせ続ける
	for (int i = 0; i < 100; i++) {

		// 出現タイミングになったら動かす
		if (frame_ >= colorful[i].delay) {
			colorful[i].active = true;
		}

		if (!colorful[i].active) {
			continue;
		}

		// 下方向へ移動
		colorful[i].ballsWt_.translation_.y += colorful[i].velocity.y;

		// 画面の下まで落ちたら上に戻す
		if (colorful[i].ballsWt_.translation_.y < -12.0f) {

			// 上のほうへ戻す
			colorful[i].ballsWt_.translation_.y = 12.0f + yDist_(gen_);

			// 横の位置も変える
			colorful[i].ballsWt_.translation_.x = xDist_(gen_);
		}

		// 行列を更新
		colorful[i].ballsWt_.TransferMatrix();
		colorful[i].ballsWt_.UpdateMatrix();
	}

	// 丸同士の当たり判定
	for (int i = 0; i < 100; i++) {

		if (!colorful[i].active) {
			continue;
		}

		for (int j = i + 1; j < 100; j++) {

			if (!colorful[j].active) {
				continue;
			}

			if (IsCollision(i, j)) {
				// 現在は接触判定のみ
			}
		}
	}
}

void changeScene::Start() {
	isStart_ = true;
	isAnimEnd_ = false;
	frame_ = 0;
}

bool changeScene::isStart() { return isStart_; }

bool changeScene::IsAnimEnd() const { return isAnimEnd_; }

void changeScene::Draw() {

	if (!isStart_) {
		return;
	}

	for (int i = 0; i < 100; i++) {

		if (colorful[i].active) {
			ballsModel_->Draw(colorful[i].ballsWt_, *camera_);
		}
	}
}
