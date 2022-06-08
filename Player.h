#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <math.h>
#include"DebugText.h"
#pragma once
///<summary>
///���L����
/// </summary>
class Player {
  public:
	///< summary>
	///������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	///������
	/// </summary>
	void Update();

	///< summary>
	///������
	/// </summary>
	void Draw(ViewProjection viewprojection);

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

