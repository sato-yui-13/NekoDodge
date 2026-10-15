#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "title.h"
#include "player.h"

#include <vector>

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
	//Enemy* enemy_;
	
	
	std::vector<Enemy*> enemies_;


	//  カメラ
	KamataEngine::Camera* camera_ = nullptr;
	// 文字と背景
	Title* title_ = nullptr;
	KamataEngine::Model* titleModel_;
	//背景用
	// playerのスプライト
	//KamataEngine::Sprite* sprite_ = nullptr;
	// playerのテクスチャ
	//uint32_t ScreenHd = 0;
};
