#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>

class Title {
public:
	Title();
	~Title();

	// 3Dモデルの初期化
	void Initialize(KamataEngine::Model* titleModel, KamataEngine::Model* spaceModel, KamataEngine::Model* screenModel, KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();
	void Background();

private:
	//titleのモデル
	KamataEngine::Model* titleModel_;
	// spaceのモデル
	KamataEngine::Model* spaceModel_;
	// screenのモデル
	KamataEngine::Model* screenModel_;

	// titleの今位置
	KamataEngine::WorldTransform titleWt_;
	// titleの今位置
	KamataEngine::WorldTransform spaceWt_;
	// titleの今位置
	KamataEngine::WorldTransform screenWt_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//文字動かす
	//タイマー
	float time_ = 0.0f;
	float wave=0.0f;
	float alpha = 0.0f;
};
