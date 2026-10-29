#pragma once
#include "KamataEngine.h"
#include <vector>
#include <random>


class Particle {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);
	
	bool IsDead() const;

	void Update();
	void Draw();


private:
	KamataEngine::Camera* camera_ = nullptr;

	//=========== particle ============
	KamataEngine::Model* particlModel_ = nullptr;
	KamataEngine::WorldTransform particleWt_;

	//方向と速さ
	KamataEngine::Vector3 velocity_;
	//粒の消える時間
	float lifeTime_ = 1.0f;

	
	
};
