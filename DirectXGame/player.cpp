#include "player.h"

using namespace KamataEngine;
player::~player() {}

void player::Initialize() {

	// 背景
	playerHd = TextureManager::Load("Player/neko.png");

	sprite_ = Sprite::Create(playerHd, {0, 0});

	position_ = {40.0f, 60.0f};
	sprite_->SetPosition(position_);
}

KamataEngine::Vector2 player::GetPosition() { return position_; }

KamataEngine::Vector2 player::GetSize() { return size_; }

bool player::IsDead() { return isDead_; }
void player::SetDead() { 
	isDead_ = true; 
}
void player::Update() {

	velocity_.x = 0.0f;
	velocity_.y = 0.0f;
	if (Input::GetInstance()->PushKey(DIK_D)) {
		velocity_.x = speed_;
	}

	if (Input::GetInstance()->PushKey(DIK_A)) {
		velocity_.x = -speed_;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		velocity_.y = -speed_;
	}

	if (Input::GetInstance()->PushKey(DIK_S)) {
		velocity_.y = speed_;
	}

	// 位置を更新
	position_.x += velocity_.x;
	position_.y += velocity_.y;

	// スプライトに反映
	sprite_->SetPosition(position_);
}

void player::Draw() {

	Sprite::PreDraw();
	if (!isDead_) {
		// 描画
		sprite_->Draw();
	}

	Sprite::PostDraw();
}
