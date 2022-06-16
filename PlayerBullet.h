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
///自キャラの弾
/// </summary>
class PlayerBullet {
  public:
	///<summary>
	///初期化
	/// <summary>
	/// <param name = "model"モデル</param>
	///<param name = "position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	///<summary>
	///更新
	/// </summary>
	void Update();

	///< summary>
	///描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

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