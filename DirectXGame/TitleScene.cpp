#include "TitleScene.h"
#include <numbers>

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() { delete sprite_; }

void TitleScene::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera) { 

	//releaseにするときエラーとして出る
	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	//worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.TransferMatrix();
}

void TitleScene::Initialize_2d() {

	// 背景
	textureHandle_ = TextureManager::Load("Title/Title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void TitleScene::Update() {
	//背景に丸いのだして動かす
	//文字に動きつける spaceの所だけ
	if (worldTransform_.translation_.z > 0.0f) {
		worldTransform_.translation_.z += 1.0f;
	}
		


}

void TitleScene::Draw() {
	Sprite::PreDraw();	
	sprite_->Draw();
	Sprite::PostDraw();
}
