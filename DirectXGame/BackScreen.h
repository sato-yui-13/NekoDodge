
#pragma once
#include "KamataEngine.h"
#include <3d/Camera.h>

class BackScreen {
public:
	BackScreen();
	~BackScreen();

	// 3Dモデルの初期化
	void Initialize(KamataEngine::Model* flourModel, KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// ボールの情報
	struct Ball {
		KamataEngine::WorldTransform flourWt_;
		KamataEngine::Vector3 velocity;
		float lifeTime = 0.0f;
	};

	// ぽわぽわする丸を10個管理
	Ball balls_[10];

	// 10個で共有するモデル
	KamataEngine::Model* flourModel_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;
};
