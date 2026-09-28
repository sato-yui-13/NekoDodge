#include "GameOver.h"
#include <Windows.h>

using namespace KamataEngine;
GameOver::GameOver() {}

GameOver::~GameOver() { delete sprite_; }

void GameOver::Initialize() {
	// 背景
	textureHandle_ = TextureManager::Load("Title/GameOver.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void GameOver::Update() {}

void GameOver::Draw() {
	Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();
}
