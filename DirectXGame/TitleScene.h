#pragma once
#include "KamataEngine.h"
#include "title.h"
#include "BackScreen.h"
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
	
	//  カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//文字と背景
	Title* title_ = nullptr;
	
	KamataEngine::Model* titleModel_;
	KamataEngine::Model* spaceModel_;
	KamataEngine::Model* screenModel_;


	//背景の動き
	BackScreen* backScreen_ = nullptr;

	KamataEngine::Model* flourModel_[10];



	
};