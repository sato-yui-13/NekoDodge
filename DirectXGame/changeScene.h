#pragma once
#include "KamataEngine.h"
#include "title.h"

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

	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* ballsModel_ = nullptr;

	Colorful colorful[100];

	bool isStart_ = false;
	bool isAnimEnd_ = false;

	int frame_ = 0;
	int landedCount_ = 0;

	static constexpr int kMaxAnimationFrames = 110;
};