#include "BackScreen.h"
#include <cmath>
#include <cstdlib>

using namespace KamataEngine;

BackScreen::BackScreen() {}
BackScreen::~BackScreen() {}

void BackScreen::Initialize(KamataEngine::Model* flourModel, KamataEngine::Camera* camera) {
	camera_ = camera;
	// assert(flourModel);

	flourModel_ = flourModel;

	for (int i = 0; i < 10; i++) {

		balls_[i].flourWt_.Initialize();
		balls_[i].flourWt_.scale_ = {2.0f, 2.0f, 2.0f};

		// 画面内に収まるように配置
		float x = static_cast<float>(rand() % 300 - 150) / 10.0f;
		float y = static_cast<float>(rand() % 200 - 100) / 10.0f;
		float z = 0.0f;

		balls_[i].flourWt_.translation_ = {x, y, z};

		// 速度設定
		balls_[i].velocity.x = static_cast<float>(rand() % 100 - 50) * 0.0005f;
		balls_[i].velocity.y = static_cast<float>(rand() % 100 - 50) * 0.0005f;

		balls_[i].flourWt_.TransferMatrix();
	}
}

void BackScreen::Update() {
	for (int i = 0; i < 10; i++) {
		balls_[i].flourWt_.translation_.x += balls_[i].velocity.x;
		balls_[i].flourWt_.translation_.y += balls_[i].velocity.y;

		// 画面端で反転

		if (std::abs(balls_[i].flourWt_.translation_.x) > 15.0f) {
			balls_[i].velocity.x *= -1.0f;
		}

		if (std::abs(balls_[i].flourWt_.translation_.y) > 10.0f) {
			balls_[i].velocity.y *= -1.0f;
		}
		balls_[i].flourWt_.UpdateMatrix();
		balls_[i].flourWt_.TransferMatrix();
	}
}

void BackScreen::Draw() {
	for (int i = 0; i < 10; i++) {
		flourModel_->Draw(balls_[i].flourWt_, *camera_);
	}
}