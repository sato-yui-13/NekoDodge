#include "title.h"
#include <numbers>

using namespace KamataEngine;
title::title() {}
title::~title() {}


void title::Initialize(Model* model, Camera* camera) {

	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	//worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.TransferMatrix();

}

void title::Update() {}

void title::Draw() {}
