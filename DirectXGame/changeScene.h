
#pragma once
#include "KamataEngine.h"
#include "title.h"
#include <random>

class changeScene {
public:
	changeScene();
	~changeScene();

	void Initialize(KamataEngine::Model* squareModel, KamataEngine::Camera* camera);
	void Update();
	void Draw();
	void Start();
	bool isStart();
	bool IsAnimEnd() const;

private:
	struct Colorful {
		KamataEngine::WorldTransform ballsWt_;
		KamataEngine::Vector3 velocity;
		int delay = 0;
		bool active = false;
		bool landed = false;
		float targetY = -12.0f;
	};

	bool IsCollision(int indexA, int indexB);

	// 乱数生成関連
	std::mt19937 gen_{std::random_device{}()};

	std::uniform_real_distribution<float> xDist_{-15.0f, 15.0f};
	std::uniform_real_distribution<float> yDist_{-10.0f, 10.0f};
	std::uniform_int_distribution<int> delayDist_{0, 120};
	std::uniform_real_distribution<float> scaleDist_{0.5f, 2.0f};

	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* ballsModel_ = nullptr;

	Colorful colorful[100];

	bool isStart_ = false;
	bool isAnimEnd_ = false;

	int frame_ = 0;
	int landedCount_ = 0;

	static constexpr int kMaxAnimationFrames = 110;
};
