#pragma once
#include "KamataEngine.h"

class Enemy {
public:
	~Enemy();

	void Initialize();
	void Update();
	void Draw();

private:
	//攻撃
	KamataEngine::Vector2 bulletPosition = {0.0f, 0.0f};
	//時間で弾出る
	float enemyTimer_ = 0.0f;
	//時間のflag
	bool isTimer_ = false;
	//speed
	float enemySpeed_ = 1.0f;

	// enemyのスプライト
	KamataEngine::Sprite* spriteBullet_ = nullptr;
	// enemyのテクスチャ
	uint32_t bulletHd = 0;




	//敵の位置
	KamataEngine::Vector2 enemyPosition = {100.0f, 400.0f};
	// 画像
	// enemyのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// enemyのテクスチャ
	uint32_t enemyHd = 0;
};
