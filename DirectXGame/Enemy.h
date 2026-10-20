#pragma once
#include "KamataEngine.h"
#include <random>

using namespace KamataEngine;
class Enemy {
public:
	~Enemy();

	void Initialize(KamataEngine::Model* enemyModel, KamataEngine::Model* ballModel, KamataEngine::Camera* camera);

	void Update();
	void Draw();
	void UpdateEntrance();
	void Move();

private:
	// 敵の位置
	// KamataEngine::Vector2 enemyPosition = {100.0f, 100.0f};

	// 敵のモデル
	KamataEngine::Model* enemyModel_;
	KamataEngine::WorldTransform enemyWt_;
	// 攻撃するball
	KamataEngine::Model* ballModel_;
	KamataEngine::WorldTransform ballWt_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// ボールの出るフラグ
	bool isLaunched_ = false;
	// 画面外からの移動
	// bool isEntering_ = false;

	// 入場
	// bool

	////ボールの速度
	float speed_ = 0.05f;
};