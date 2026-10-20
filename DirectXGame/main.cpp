#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;
GameScene* gameScene = nullptr;
GameOver* gameOver = nullptr;

GameClear* gameClear = nullptr;

Camera camera_;

// BGM
// uint32_t BGMHandle = 0;
// uint32_t voiceHandle = 0;
// シーン用ポインタ
TitleScene* titleScene = nullptr;
// シーン
enum class Scene { kTitle, kGame, kOver, kClear };

// 現在のシーン
Scene scene = Scene::kTitle;

// 前回のシーン
Scene oldScene = Scene::kGame;
float gameTimer = 0.0f;
// シーン切り替え
void ChangeScene() {

	if (scene == oldScene) {
		return;
	}

	switch (scene) {

	case Scene::kTitle:
		delete gameOver;
		gameOver = nullptr;

		// カメラを初期位置に戻す
		camera_.Initialize();
		camera_.translation_ = {0, 40, -20};
		camera_.rotation_.x = 0.2f;
		camera_.UpdateMatrix();

		titleScene = new TitleScene();
		titleScene->Initialize();

		break;

	case Scene::kGame:
		// OutputDebugStringA("Create GameScene\n");
		delete titleScene;
		titleScene = nullptr;

		gameScene = new GameScene();

		gameScene->Initialize();
		gameTimer = 0.0f; // ★ここでリセット
		break;
	case Scene::kOver:

		delete gameScene;
		gameScene = nullptr;

		gameOver = new GameOver();
		gameOver->Initialize();

		break;
	case Scene::kClear:

		delete gameScene;
		gameScene = nullptr;

		gameClear = new GameClear();
		gameClear->Initialize();
		break;
	}

	oldScene = scene;
}

// 更新
void SceneUpdate() {

	gameTimer += 1.0f / 60.0f;
	switch (scene) {

	case Scene::kTitle:

		titleScene->Update();
		//アニメーション終わり次第ゲームシーンへ
		if (titleScene->IsAnimEnd()) {
			scene = Scene::kGame;
			ChangeScene();
			return;
		}

		break;

	case Scene::kGame:

		gameScene->Update();

		
		//if (gameTimer >= 30.0f) {
		//	scene = Scene::kClear;
		//	ChangeScene();
		//}

		break;

	case Scene::kOver:

		gameOver->Update();
		// エンターキーを押したらtitleへ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			scene = Scene::kTitle;
			ChangeScene();
			return;
		}
		break;

	case Scene::kClear:

		gameClear->Update();
		// エンターキーを押したらtitleへ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			scene = Scene::kTitle;
			ChangeScene();
		}

		break;
	}
}

// 描画
void SceneDraw() {

	switch (scene) {

	case Scene::kTitle:
		
		titleScene->Draw();
		break;

	case Scene::kGame:

		gameScene->Draw();

		break;
	case Scene::kOver:

		gameOver->Draw();

		break;
	case Scene::kClear:
		gameClear->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// サウンドデータの読み込み
	// BGMHandle = Audio::GetInstance()->LoadWave("bgm/Shimmering.mp3");
	// voiceHandle = Audio::GetInstance()->PlayWave(BGMHandle, true, 0.2f);

	camera_.Initialize();
	camera_.translation_ = {0, 0, -20};
	camera_.rotation_.x = 0.2f;
	camera_.UpdateMatrix();

	// メインループ
	while (true) {
		// エンジンの更新

		if (KamataEngine::Update()) {
			break;
		}

		ChangeScene();
		SceneUpdate();

		dxCommon->PreDraw();
		SceneDraw();
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	KamataEngine::Finalize();

	return 0;
}