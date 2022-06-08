#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	//テクスチャハンドル
	uint32_t textureHandle = 0;
	// 3Dモデル
	Model* model = nullptr;
	//ワールドトランスフォームビュープロジェクション
	WorldTransform worldTransform;
	//ビュープロジェクション
	ViewProjection viewProjection;
	//デバックカメラ
	DebugCamera* debugCamera = nullptr;
	Vector3 ten[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
	  {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };

	int hen2[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},

	  {4, 5},
      {5, 6},
      {6, 7},
      {7, 4},

	  {0, 4},
      {1, 5},
      {2, 6},
      {3, 7},
	};
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};