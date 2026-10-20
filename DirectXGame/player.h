#pragma once
#include "KamataEngine.h"
#include "math/Matrix4x4.h"
#include "math/Vector3.h"

class player {
public:
	// player();
	~player();

	void Initialize(KamataEngine::Model* playerModel, KamataEngine::Camera* camera);

	//キー入力
	void InputMove();

	//入場
	void UpdateEntrance();

	bool IsEntrance() { return isEntrance_; }
	
	//最初の操作　ゲームスタート前 操作確認
	//void CheckTutorialInput();

	void Update();

	void Draw();



private:
	// プレイヤーのモデル
	KamataEngine::Model* playerModel_;
	KamataEngine::WorldTransform playerWt_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;


	// 速度
	KamataEngine::Vector2 velocity_ = {0.1f, 0.1f};
	
	//========== 入場 ============
	//入場中か　これですたーとする
	bool isEntrance_ = false;
	//最初の位置
	KamataEngine::Vector2 entranceStart_ = {-10.0f, -7.0f,};
	////最後の位置
	KamataEngine::Vector2 entranceEnd_ = {0.0f, 0.0f};
	//startタイマー
	float entranceTimer_ = 0.0f;
	//経過時間
	float entranceDuration_ = 1.0f;

	//======== チュートリアル(操作) ===========
	//チュートリアルフラグ
	bool isTutorial = false;
	//入力操作の確認フラグ
	//bool isMoveW_ = false;
	//bool isMoveA_ = false;
	//bool isMoveS_ = false;
	//bool isMoveD_ = false;
	
};
