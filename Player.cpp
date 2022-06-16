#include "Player.h"
#include "Audio.h"
#include "AxisIndicator.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Transform.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタをチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
}
void Player::Update() {
	Vector3 move = {0, 0, 0};

	const float CharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move = {-CharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {CharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_UP)) {
		move = {0, CharacterSpeed, 0};
	} else if (input_->PushKey(DIK_DOWN)) {
		move = {0, -CharacterSpeed, 0};
	}
	worldTransform_.translation_ += move;

	affinMove::Translate(worldTransform_);

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);

	//移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 15;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewprojection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}
