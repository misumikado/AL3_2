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
///自キャラ
/// </summary>
class Player {
  public:
	///< summary>
	///初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	///初期化
	/// </summary>
	void Update();

	///< summary>
	///初期化
	/// </summary>
	void Draw(ViewProjection viewprojection);

  private:
	//ワールド返還データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

