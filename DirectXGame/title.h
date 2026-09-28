#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>

class title {
public:
	title();
	~title();

	// 3Dモデルの初期化
	void Initialize(Model* titleModel, Model* spaceModel, Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	//titleのモデル
	KamataEngine::Model* titleModel_ = nullptr;
	// titleの今位置
	WorldTransform titleWt_;

	//spaceのモデル
	KamataEngine::Model* spaceModel_ = nullptr;
	// titleの今位置
	WorldTransform spaceWt_;

	// カメラ
	Camera* camera_ = nullptr;
};
