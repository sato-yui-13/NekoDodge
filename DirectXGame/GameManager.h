
#pragma once

#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// シーン
	enum class Scene { kTitle, kGame, kOver, kClear };

	// シーン切り替え
	void ChangeScene();

	// 現在と前回のシーン
	Scene scene_ = Scene::kTitle;
	Scene oldScene_ = Scene::kGame;

	// 各シーンのポインタ
	GameScene* gameScene_ = nullptr;
	GameOver* gameOver_ = nullptr;
	GameClear* gameClear_ = nullptr;
	TitleScene* titleScene_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// タイマー
	float gameTimer_ = 0.0f;
	float clearTimer_ = 0.0f;
	bool isClearEffect_ = false;

	// 白くなるスプライト
	uint32_t whiteTextureHandle_ = 0;
	KamataEngine::Sprite* whiteSprite_ = nullptr;
};
