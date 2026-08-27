#pragma once
#include "KamataEngine.h"
// ゲームシーン
class TitleScene {
public:
	TitleScene();
	~TitleScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// 背景
	KamataEngine::Sprite* sprite_ = nullptr;
	//// タイトル名
	//KamataEngine::Sprite* shotGame_ = nullptr;
	//// エンターキーを押す
	//KamataEngine::Sprite* hitkey_ = nullptr;

	// 背景
	uint32_t textureHandle_ = 0;
	//// タイトル名
	//uint32_t sgHandle_ = 0;
	//// エンターキー
	//uint32_t hkHandle_ = 0;

	//// タイトルを移動させる
	//KamataEngine::Vector2 position_;
	//// 止まる位置
	//KamataEngine::Vector2 targetPosition_ = {0, 45};

	//// 落下速度
	//float moveSpeed_ = 5.0f;

	//bool shotGameMove_ = true;

	//// キーの説明を点滅させる
	//float hitkeyTimer_ = 0.0f;
};