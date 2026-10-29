#include "Particle.h"
#include <cmath>

using namespace KamataEngine;

void Particle::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity) {
	particlModel_ = model;
	camera_ = camera;
	velocity_ = velocity;

	particleWt_.Initialize();
	particleWt_.translation_=position;
	particleWt_.TransferMatrix();
	particleWt_.UpdateMatrix();
}

bool Particle::IsDead() const { return lifeTime_ <= 0.0f; }

void Particle::Update() {
	particleWt_.translation_.x += velocity_.x;
	particleWt_.translation_.y += velocity_.y;
	
	lifeTime_  -= 1.0f / 60.0f;

	particleWt_.UpdateMatrix();
}

void Particle::Draw() { particlModel_->Draw(particleWt_, *camera_); }
