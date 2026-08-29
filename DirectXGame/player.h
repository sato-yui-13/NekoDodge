#pragma once
#include "KamataEngine.h"
#include <2d/Sprite.h>

class player {
public:
	// player();
	~player();

	void Initialize();
	void Update();
	void Draw();

	//位置
	KamataEngine::Vector2 GetPosition();
	//当たり判定
	KamataEngine::Vector2 GetSize();
	
	
	

		// 死亡フラグ
	bool IsDead() const { return isDead_; }

	// 死亡させる
	void SetDead() { isDead_ = true; }

private:

	// 当たり判定用の数字
	KamataEngine::Vector2 size_ = {64.0f, 64.0f};
	// 死亡フラグ
	bool isDead_ = false;

	// 位置
	KamataEngine::Vector2 position_ = {630, 450};
	// 速度
	KamataEngine::Vector2 velocity_ = {0, 0};
	//
	float speed_ = 4.0f;
	//playerのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// playerのテクスチャ
	uint32_t playerHd = 0;

};
