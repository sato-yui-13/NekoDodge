#pragma once

#include "KamataEngine.h"

class Collision {
public:
	// 矩形同士の当たり判定
	static bool Check(KamataEngine::Vector2 pos1, KamataEngine::Vector2 size1, KamataEngine::Vector2 pos2, KamataEngine::Vector2 size2);
};