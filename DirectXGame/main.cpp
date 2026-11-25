
#include "GameManager.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジン初期化
	KamataEngine::Initialize();

	// ゲーム管理クラス
	GameManager* gameManager = new GameManager();
	gameManager->Initialize();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// ゲーム更新
		gameManager->Update();

		// 描画
		dxCommon->PreDraw();

		gameManager->Draw();

		dxCommon->PostDraw();
	}

	// ゲーム管理クラスの解放
	delete gameManager;
	gameManager = nullptr;

	// エンジン終了
	KamataEngine::Finalize();

	return 0;
}
