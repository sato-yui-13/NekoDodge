#pragma once
#include "KamataEngine.h"

class Enemy {
public:
	~Enemy();

	void Initialize();
	
	void Update();
	void Draw();

	// 移動の処理
	void Move();

	//Bulletの処理
	void Bullet();

	//二回目の弾
	void Second();

	//三回目の弾(扇型)
	void Third();


	//位置
	KamataEngine::Vector2 GetPosition();
	// 当たり判定
	KamataEngine::Vector2 GetSize();

private:

	// 当たり判定用の変数
	KamataEngine::Vector2 size_ = {4.0f, 4.0f};
	
	//攻撃
	KamataEngine::Vector2 bulletPosition[3];
	//時間で弾出る
	float enemyTimer_ = 0.0f;
	//時間のflag
	bool isTimer_ = false;
	//speed
	float bulletSpeed_ = 5.0f;
	// 弾の速度（3発分）
	KamataEngine::Vector2 bulletVelocity[3];



	// enemyのスプライト
	KamataEngine::Sprite* spriteBullet[3] = {};
	// enemyのテクスチャ
	uint32_t bulletHd = 0;

	//敵の位置
	KamataEngine::Vector2 enemyPosition = {1380.0f, 100.0f};
	// 敵を止めたい位置
	KamataEngine::Vector2 targetEnemy_ = {630.0f, 100.0f};
	//スピード
	float enemySpeed_ = 6.0f;
	
	//============== 二個目の段階 ==============//
	// 攻撃段階
	bool isFirstAttack_ = true;
	//二回目の攻撃flag
	bool isSecondAttack_ = false;
	//描画フラグ
	bool isBulletActive_ = false;
	//三回目のフラグ
	bool isThirdAttack_ = false;




	// 画像
	// enemyのスプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// enemyのテクスチャ
	uint32_t enemyHd = 0;
};
