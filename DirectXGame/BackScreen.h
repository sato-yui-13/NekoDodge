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

	struct Ball {
		KamataEngine::WorldTransform flourWt_;
		KamataEngine::Vector3 velocity;
		float lifeTime;
	};

	 // ぽわぽわする丸
	Ball balls_[10];
	
	// 八方向に行く弾
	KamataEngine::Model* flourModel_;  

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	
};
