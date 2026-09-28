#include "title.h"
#include <numbers>

using namespace KamataEngine;
title::title() {}
title::~title() {}

void title::Initialize(Model* titleModel, Model* spaceModel, Camera* camera) {
	assert(titleModel);
	assert(spaceModel);
	assert(camera);
	
	//title
	titleModel_ = titleModel;
	titleWt_.Initialize();
	titleWt_.translation_ = {0.0f, 0.0f, 0.0f};
	titleWt_.TransferMatrix();

	//space
	spaceModel_ = spaceModel;
	spaceWt_.Initialize();
	spaceWt_.translation_ = {0.0f, -3.0f, 0.0f};
	spaceWt_.TransferMatrix();

	//camera
	camera_ = camera;

}




void title::Update() {}

void title::Draw() {}
