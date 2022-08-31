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
#include "BulletVector3.h"
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

//自機のクラスの前方宣言
class Player;

class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();
	void Attack();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }
	void Draw(ViewProjection& viewProjection);

	//発射間隔
	static const int kFireInterval = 60;

	void SetPlayer(Player* player) { player_ = player; }

	float radius = 3.0f;

  private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;

	//フェーズ
	Phase phase_ = Phase::Approach;
	//Bullet
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//タイマー
	int32_t FireTimer = 0;
	//Player
	Player* player_ = nullptr;
};