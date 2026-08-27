#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;
GameScene* gameScene = nullptr;
// シーン用ポインタ
TitleScene* titleScene = nullptr;
// シーン
enum class Scene { kTitle, kGame };

// 現在のシーン
Scene scene = Scene::kTitle;

// 前回のシーン
Scene oldScene = Scene::kGame;

// シーン切り替え
void ChangeScene() {

	if (scene == oldScene) {
		return;
	}

	switch (scene) {

	case Scene::kTitle:

		delete gameScene;
		gameScene = nullptr;

		titleScene = new TitleScene();
		titleScene->Initialize();

		break;

	case Scene::kGame:
		// OutputDebugStringA("Create GameScene\n");
		delete titleScene;
		titleScene = nullptr;

		gameScene = new GameScene();
		gameScene->Initialize();

		break;
	}

	oldScene = scene;
}

// 更新
void SceneUpdate() {
	switch (scene) {

	case Scene::kTitle:

		 titleScene->Update();

		// エンターキーを押したらゲームへ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			scene = Scene::kGame;
			ChangeScene();
		}

		break;

	case Scene::kGame:
		gameScene->Update();

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
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	

	

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