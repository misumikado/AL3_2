#include "GameScene.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>
#include"PlayerBullet.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^���`�F�b�N
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("black.png");

	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Player::Update() {
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	}