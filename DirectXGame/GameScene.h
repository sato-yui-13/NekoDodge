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
	
	//========= player ===========
	player* player_=nullptr;
	KamataEngine::Model* playerModel_;
	bool isPlayerDead_ = false;
	//入場開始


	//=========== 敵 ==============
	Enemy* enemy_ = nullptr;
	KamataEngine::Model* enemyModel_;
	bool isEnemyEntranceStarted_ = false;
	//KamataEngine::WorldTransform *target_,
	
	//========== パーティクル ============
	std::vector<Particle*> particles_;
	KamataEngine::Model* particleModel_ = nullptr;

	//========= 背景 ===========
	KamataEngine::Model* backgroundModel_ = nullptr;
	KamataEngine::WorldTransform backgroundTransform_;


	
	//========= カメラ ===========  
	KamataEngine::Camera* camera_ = nullptr;
	
};
