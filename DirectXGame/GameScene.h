#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "Particle.h"
#include "title.h"
#include "player.h"

#include <vector>

// ゲームシーン
class GameScene {
public:
	/// デストラクタ
	GameScene();
	~GameScene();

	/// 初期化
	void Initialize();

	bool IsPlayerDead() const;

	//演出終わりの
	bool IsExplosionFinished() const;

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:

	//死んだあと
	void CreateEnemy();

	//========= player ===========
	player* player_=nullptr;
	KamataEngine::Model* playerModel_;
	bool isPlayerDead_ = false;
	//入場開始


	//=========== 敵 ==============
	std::vector<Enemy*> enemies_;
	KamataEngine::Model* enemyModel_;
	bool isEnemyEntranceStarted_ = false;
	KamataEngine::WorldTransform* target_ = nullptr;
	//KamataEngine::WorldTransform *target_,
	//攻撃パターンのカウント
	int enemySpawnCount_ = 0;
	// 何対でているか
	int enemiesPerWave_ = 1;

	
	//========== パーティクル ============
	std::vector<Particle*> particles_;
	KamataEngine::Model* particleModel_ = nullptr;

	//========= 背景 ===========
	KamataEngine::Model* backgroundModel_ = nullptr;
	KamataEngine::WorldTransform backgroundTransform_;


	
	//========= カメラ ===========  
	KamataEngine::Camera* camera_ = nullptr;
	float gameTimer_ = 0.0f;
	
};
