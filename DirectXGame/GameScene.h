#pragma once
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

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	player* player_;
	Enemy* enemy_;
	TrackingEnemy* trackingEnemy_;

	// カメラ
	KamataEngine::Camera camera_;
};
