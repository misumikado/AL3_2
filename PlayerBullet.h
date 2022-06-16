#include "GameScene.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

#pragma once
///<summary>
///���L�����̒e
/// </summary>
class PlayerBullet {
  public:
	///<summary>
	///������
	/// <summary>
	/// <param name = "model"���f��</param>
	///<param name = "position">�������W</param>
	void Initialize(Model* model, const Vector3& position);

	///<summary>
	///�X�V
	/// </summary>
	void Update();

	///< summary>
	///�`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	private:
	//���[���h�Ԋ҃f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};