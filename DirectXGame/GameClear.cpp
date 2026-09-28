#include "GameClear.h"
#include <Windows.h>

using namespace KamataEngine;
GameClear::GameClear() {}

GameClear::~GameClear() { delete sprite_; }

void GameClear::Initialize() {
	// 背景
	textureHandle_ = TextureManager::Load("Title/GameClear.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void GameClear::Update() {}

void GameClear::Draw() {
	Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();
}
