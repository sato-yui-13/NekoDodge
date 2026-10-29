#pragma once
#include "KamataEngine.h"
// ゲームシーン
class GameOver {
public:
	GameOver();
	~GameOver();

	// 初期化
	void Initialize();

	//選択
	void SelectMenu();

	//決定
	int ConfirmSelection();

	int GetSelectIndex() { return selectIndex_; }
	// 更新
	void Update();

	// 描画
	void Draw();

private:
	//========= カメラ ===========
	KamataEngine::Camera* camera_ = nullptr;

	//========= 背景 ===========
	KamataEngine::Model* backgroundModel_ = nullptr;
	KamataEngine::WorldTransform backgroundwt_;

	//============= ゲームオーバー ================
	KamataEngine::Model* gOModel_ = nullptr;
	KamataEngine::WorldTransform gOwt_;

	//============= リスタート  ==================
	KamataEngine::Model* reStartModel_ = nullptr;
	KamataEngine::WorldTransform reStartwt_;

	//============== タイトル =================
	KamataEngine::Model* titleModel_ = nullptr;
	KamataEngine::WorldTransform titlewt_;

	//================= 色 ================
	KamataEngine::ObjectColor restartColor_;
	KamataEngine::ObjectColor titleColor_;


	//============= 選択 ===============
	int selectIndex_ = 0;

};