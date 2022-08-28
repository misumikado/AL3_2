#pragma once
#include "Model.h"
#include "WorldTransform.h"

class EnemyBullet {
  public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	//���x
	Vector3 velocity_;
	//����
	static const int32_t LifeTime = 60 * 5;
	//�^�C�}�[
	int32_t deathTimer_ = LifeTime;
	//���S����
	bool isDead_ = false;
};