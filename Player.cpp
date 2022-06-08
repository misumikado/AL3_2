#include"Player.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include"Model.h"

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
void Player::Update(){ 
	Vector3 move = {0,0,0};

	const float CharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {


		move = {-CharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {CharacterSpeed, 0, 0};
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}


void Player::Draw(ViewProjection viewprojection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_,viewprojection, textureHandle_);
}

