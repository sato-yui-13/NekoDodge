#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>
// ゲームシーン
class TitleScene {
public:
	TitleScene();
	~TitleScene();

	// 3Dモデルの初期化
	void Initialize(Model* model, Camera* camera);
	// 2D用の初期化
	void Initialize_2d();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;

	// 今位置
	WorldTransform worldTransform_;

	// 背景
	KamataEngine::Sprite* sprite_ = nullptr;
	// 背景
	uint32_t textureHandle_ = 0;
};