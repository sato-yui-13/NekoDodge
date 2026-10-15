#pragma once
#include "KamataEngine.h"
#include "title.h"
#include "changeScene.h"
#include "BackScreen.h"
// ゲームシーン
class TitleScene {
public:
	TitleScene();
	~TitleScene();
	
	// 初期化
	void Initialize(KamataEngine::Camera* camera);

	

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終わりの判定
	bool IsAnimEnd() const { return changeScene_->IsAnimEnd(); }

private:
	
	//  カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//文字と背景
	Title* title_ = nullptr;
	// 背景の動き
	BackScreen* backScreen_ = nullptr;
	
	//シーン切り替えアニメーション
	changeScene* changeScene_ = nullptr;



	KamataEngine::Model* titleModel_;
	KamataEngine::Model* spaceModel_;
	KamataEngine::Model* screenModel_;

	KamataEngine::Model* colorfulModel_[100];

	

	KamataEngine::Model* flourModel_[10];

	

	
};