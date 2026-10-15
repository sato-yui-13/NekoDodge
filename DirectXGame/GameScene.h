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

	//player* GetPlayer() { return player_; }

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	//player* player_;
	Enemy* enemy_;
	
	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::Model* bulletModel_ = nullptr;

	std::vector<Enemy*> enemies_;


	//  カメラ
	KamataEngine::Camera* camera_;
	
	KamataEngine::Model* titleModel_;
	KamataEngine::Vector2 enemyPosition_;
};
