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
	GameScene();
	~GameScene();

	/// 初期化
	void Initialize();

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	
	//========= player ===========
	player* player_=nullptr;
	KamataEngine::Model* playerModel_;
	//入場開始


	//=========== 敵 ==============
	Enemy* enemy_ = nullptr;
	KamataEngine::Model* enemyModel_;
	bool isEnemyEntranceStarted_ = false;
	//KamataEngine::WorldTransform *target_,
	



	//========= 背景 ===========
	KamataEngine::Model* backgroundModel_ = nullptr;
	KamataEngine::WorldTransform backgroundTransform_;


	
	//========= カメラ ===========  
	KamataEngine::Camera* camera_ = nullptr;
	
};
