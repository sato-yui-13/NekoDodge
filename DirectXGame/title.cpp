#include "title.h"
#include <numbers>

using namespace KamataEngine;
Title::Title() {}
Title::~Title() {}

void Title::Initialize(Model* titleModel, Model* spaceModel, Model* screenModel, Camera* camera) {
	//assert(titleModel);
//	assert(spaceModel);
	//assert(camera);

	// title
	titleModel_ = titleModel;
	titleWt_.Initialize();
	titleWt_.translation_ = {0.0f, 0.0f, 0.0f};
	titleWt_.TransferMatrix();

	// space
	spaceModel_ = spaceModel;
	spaceWt_.Initialize();
	spaceWt_.translation_ = {0.0f, -10.0f, 0.0f};
	// spaceWt_.rotation_.z = std::numbers::pi_v<float> / 2.0f;
	spaceWt_.TransferMatrix();

	// title
	screenModel_ = screenModel;
	screenWt_.Initialize();
	screenWt_.translation_ = {0.0f, 0.0f, 0.0f};
	screenWt_.TransferMatrix();

	// camera
	camera_ = camera;
}

void Title::Update() {

	// spaceの文字をグラデーションにする
	time_ += 0.03f;
	wave = (sinf(time_) + 1.0f) * 0.5f;
	alpha = 0.15f + wave * 0.85f;

	// SPACEモデルに透明度を反映
	spaceModel_->SetAlpha(alpha);

	
}

void Title::Draw() {

	// たいとる
	titleModel_->Draw(titleWt_, *camera_);
	// すぺーす
	spaceModel_->Draw(spaceWt_, *camera_);
}

void Title::Background() { // 背景
	screenModel_->Draw(screenWt_, *camera_);
}
