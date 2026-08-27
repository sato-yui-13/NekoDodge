#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;
TitleScene::TitleScene() {}

TitleScene::~TitleScene() { delete sprite_; }

void TitleScene::Initialize() {
	// 背景
	textureHandle_ = TextureManager::Load("Title/Title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void TitleScene::Update() {}

void TitleScene::Draw() {
	Sprite::PreDraw();	
	sprite_->Draw();
	Sprite::PostDraw();
}
