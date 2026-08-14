#include "TrackingEnemy.h"
using namespace KamataEngine;
TrackingEnemy::~TrackingEnemy() {}

void TrackingEnemy::Initialize() {

	// 左の敵
	LeftHd = TextureManager::Load("TrackingEnemy/enemyLeft.png");
	left = Sprite::Create(LeftHd, enemyLeft_);
	// 左の敵
	RightHd = TextureManager::Load("TrackingEnemy/enemyRight.png");
	right_ = Sprite::Create(RightHd, enemyRight_);



}

void TrackingEnemy::Movaementeft() {
	// 左から右へ移動
	if (enemyLeft_.x < targetLeft_.x) {

		enemyLeft_.x += LeftSpeed_;

		// 目標地点を通り過ぎないようにする
		if (enemyLeft_.x > targetLeft_.x) {
			enemyLeft_.x = targetLeft_.x;
		}
	}
	// スプライトの位置を更新
	left->SetPosition(enemyLeft_);
}

void TrackingEnemy::Update() { 
	
	Movaementeft();

}

void TrackingEnemy::Draw() {
	Sprite::PreDraw();
	// 描画
	left->Draw();
	right_->Draw();

	Sprite::PostDraw();
}
