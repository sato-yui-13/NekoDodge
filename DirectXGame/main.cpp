#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーン生成
	GameScene* gameScene = new GameScene();

	// 初期化
	gameScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新

		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		dxCommon->PreDraw();

		gameScene->Draw();

		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	KamataEngine::Finalize();

	return 0;
}