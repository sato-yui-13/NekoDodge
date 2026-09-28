#include "TitleScene.h"
#include <numbers>

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() { delete sprite_; }

void TitleScene::Initialize_2d() {
	// 背景
	textureHandle_ = TextureManager::Load("Title/Title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void TitleScene::Update() {
}

void TitleScene::Draw() {
	Sprite::PreDraw();	
	sprite_->Draw();
	Sprite::PostDraw();
}
