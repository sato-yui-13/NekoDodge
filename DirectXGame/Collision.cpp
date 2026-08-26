#include "Collision.h"

using namespace KamataEngine;

bool Collision::Check(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2) {

	// 横方向の判定
	if (pos1.x + size1.x < pos2.x || pos2.x + size2.x < pos1.x) {
		return false;
	}

	// 縦方向の判定
	if (pos1.y + size1.y < pos2.y || pos2.y + size2.y < pos1.y) {
		return false;
	}

	// 重なっている
	return true;
}