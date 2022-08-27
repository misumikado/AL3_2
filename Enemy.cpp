#include "Enemy.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Enemy::Initalize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
}

void Enemy::Update() {
	Vector3 move = {0, 0, 0};
	//�ړ��x�N�g���̕ύX���鏈��
	/*if (input_->PushKey(DIK_W)) {
	    move.y += 0.5f;
	} else if (input_->PushKey(DIK_S)) {
	    move.y -= 0.5f;
	} else if (input_->PushKey(DIK_A)) {
	    move.x -= 0.5f;
	} else if (input_->PushKey(DIK_D)) {
	    move.x += 0.5f;
	}*/

	move.z -= 0.2;
	//���W�ړ�(�x�N�g�����Z)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);

#pragma region �ړ�����
	//�ړ����E���W
	const float MoveLimitX = 35.0f;
	const float MoveLimitY = 20.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransforms_.translation_.x = max(worldTransforms_.translation_.x, -MoveLimitX);
	worldTransforms_.translation_.x = min(worldTransforms_.translation_.x, +MoveLimitX);
	worldTransforms_.translation_.y = max(worldTransforms_.translation_.y, -MoveLimitY);
	worldTransforms_.translation_.y = min(worldTransforms_.translation_.y, +MoveLimitY);
#pragma endregion

	//�s��X�V
	worldTransforms_.TransferMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
}
