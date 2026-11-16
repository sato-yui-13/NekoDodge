
	#pragma once
#include "KamataEngine.h"
class PlayerBullet {
	public:
	
		void Initialize(KamataEngine::Model* playerBollModel, KamataEngine::Camera* camera, KamataEngine::Vector2 direction, KamataEngine::Vector3 position);

		//位置取得
		KamataEngine::Vector3 GetPosition();

		void Update();

		void Draw();

		
	private:
		// プレイヤーのモデル
		KamataEngine::Model* playerBollModel_;
	    KamataEngine::WorldTransform playerBollWt_;

		//方向
	    KamataEngine::Vector2 direction_ ;
		// カメラ
		KamataEngine::Camera* camera_ = nullptr;

		//スピード
	    float speed_ = 0.1f;

};
