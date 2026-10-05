#pragma once
#include "KamataEngine.h"
#include "title.h"

// ゲームシーン
class TitleScene {
public:
	TitleScene();
	~TitleScene();
	
	// 2D用の初期化
	void Initialize(KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

private:

	//3Dモデル
	Title* title_ = nullptr;

	//タイトル
	KamataEngine::Model* titleModel_;

	//スペース
	KamataEngine::Model* spaceModel_;

	// screenのモデル
	KamataEngine::Model* screenModel_;


	////  カメラ
	KamataEngine::Camera* camera_ = nullptr;
};