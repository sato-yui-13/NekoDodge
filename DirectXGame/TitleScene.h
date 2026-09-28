#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>
// ゲームシーン
class TitleScene {
public:
	TitleScene();
	~TitleScene();

	
	// 2D用の初期化
	void Initialize_2d();

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