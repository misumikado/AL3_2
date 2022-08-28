#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include <math.h>
#include <memory>

//行動フェーズ
enum class Phase {
	Approach, //接近する
	Leave,    //離脱する
};

class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();
	void Attack();

	void Draw(ViewProjection& viewProjection);

	//発射間隔
	static const int kFireInterval = 60;

  private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//フェーズ
	Phase phase_ = Phase::Approach;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//発射タイマー
	int32_t FireTimer = 0;
};
