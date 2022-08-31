#pragma once
#include "Model.h"
#include "WorldTransform.h"

class EnemyBullet {
  public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }
	float radius = 3.0f;

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	//速度
	Vector3 velocity_;

	//消滅時間
	static const int32_t LifeTime = 60 * 5;
	
	//タイマー
	int32_t deathTimer_ = LifeTime;
	
	//死亡フラグ
	bool isDead_ = false;
};