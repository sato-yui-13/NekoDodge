#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "TrackingEnemy.h"
#include "player.h"

// ゲームシーン
class GameScene {
public:
	/// デストラクタ
	~GameScene();

	/// 初期化
	void Initialize();

	//enemyの当たり判定
	void CheckCollisionEnemy();

	player* GetPlayer() { return player_; }

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	player* player_;
	Enemy* enemy_;
	TrackingEnemy* trackingEnemy_;
	//Collision* collision_;

	// カメラ
	KamataEngine::Camera camera_;


	//背景用
	// playerのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// playerのテクスチャ
	uint32_t ScreenHd = 0;
};
