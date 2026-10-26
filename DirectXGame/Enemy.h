#pragma once
#include "Bullet.h"
#include "KamataEngine.h"
#include <vector>
#include <random>

using namespace KamataEngine;

class player;


class Enemy {
public:
	~Enemy();

	void Initialize(KamataEngine::Model* enemyModel, KamataEngine::WorldTransform* target, KamataEngine::Camera* camera, player* player);

	//入場フラグ
	void UpdateEntrance();

	void Move();


	void Update();
	void Draw();


	bool IsEntranceFinished() { return isEntranceFinished_; };


private:
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//========== Bullet =============
	std::vector<Bullet*> bullets_;
	KamataEngine::WorldTransform* target_;
	KamataEngine::Model* bollModel_;
	player* player_ = nullptr;


	//========== 敵のモデル ==============
	KamataEngine::Model* enemyModel_;
	KamataEngine::WorldTransform enemyWt_;
	

	

	// ボールの出るフラグ
	//bool isLaunched_ = false;
	bool isEntranceFinished_ = false;


	////ボールの速度
	float speed_ = 0.05f;
};