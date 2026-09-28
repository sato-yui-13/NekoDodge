#pragma once
#include "KamataEngine.h"
// ゲームシーン
class GameClear {
public:
	GameClear();
	~GameClear();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// 背景
	KamataEngine::Sprite* sprite_ = nullptr;

	// 背景
	uint32_t textureHandle_ = 0;
};