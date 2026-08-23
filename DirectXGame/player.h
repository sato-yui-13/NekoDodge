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

private:

	//当たり判定用の数字
	Vector2 playerSize_ = {64.0f, 64.0f};
	// 位置
	KamataEngine::Vector2 position_ = {0, 0};

	// 速度
	KamataEngine::Vector2 velocity_ = {0, 0};

	//playerのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// playerのテクスチャ
	uint32_t playerHd = 0;

};
