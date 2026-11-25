
#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "Particle.h"
#include "player.h"
#include "title.h"

#include <vector>

// ゲームシーン
class GameScene {
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// プレイヤー死亡判定
	bool IsPlayerDead() const;

	// 演出終了判定
	bool IsExplosionFinished() const;

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// 敵生成
	void CreateEnemy();

	//========= player ===========
	player* player_ = nullptr;
	KamataEngine::Model* playerModel_ = nullptr;
	bool isPlayerDead_ = false;

	//=========== 敵 ==============
	std::vector<Enemy*> enemies_;
	KamataEngine::Model* enemyModel_ = nullptr;
	bool isEnemyEntranceStarted_ = false;

	// 攻撃パターンのカウント
	int enemySpawnCount_ = 0;

	// 何体出ているか
	int enemiesPerWave_ = 1;

	//========== パーティクル ============
	std::vector<Particle*> particles_;
	KamataEngine::Model* particleModel_ = nullptr;

	//========= 背景 ===========
	KamataEngine::Model* backgroundModel_ = nullptr;
	KamataEngine::WorldTransform backgroundTransform_;

	//========= カメラ ===========
	KamataEngine::Camera* camera_ = nullptr;

	// ゲーム時間
	float gameTimer_ = 0.0f;
};
