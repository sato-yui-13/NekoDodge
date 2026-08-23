#include "TrackingEnemy.h"
using namespace KamataEngine;
TrackingEnemy::~TrackingEnemy() {}

void TrackingEnemy::Initialize() {

	// 左の敵
	LeftHd = TextureManager::Load("TrackingEnemy/enemyLeft.png");
	left_ = Sprite::Create(LeftHd, enemyLeft_);
	// 左の敵
	RightHd = TextureManager::Load("TrackingEnemy/enemyRight.png");
	right_ = Sprite::Create(RightHd, enemyRight_);



}

void TrackingEnemy::MoveLeft() {
	// 左から右へ移動
	if (enemyLeft_.x < targetLeft_.x) {

		enemyLeft_.x += LeftSpeed_;

		// 目標地点を通り過ぎないようにする
		if (enemyLeft_.x > targetLeft_.x) {
			enemyLeft_.x = targetLeft_.x;
		}
	}
	// スプライトの位置を更新
	left_->SetPosition(enemyLeft_);
}

void TrackingEnemy::MoveRight() {
	// 右から左へ移動
	if (enemyRight_.x > targetRight_.x) {
		enemyRight_.x -= RightSpeed_;
	}

	// 目標地点を通り過ぎないようにする
	if (enemyRight_.x < targetRight_.x) {
		enemyRight_.x = targetRight_.x;
	}

	right_->SetPosition(enemyRight_);
}

void TrackingEnemy::Update() { 
	
	MoveLeft();
	MoveRight();
}

void TrackingEnemy::Draw() {
	Sprite::PreDraw();
	// 描画
	left_->Draw();
	right_->Draw();

	Sprite::PostDraw();
}
