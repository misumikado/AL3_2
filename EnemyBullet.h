#pragma once
#include "Model.h"
#include "WorldTransform.h"

class EnemyBullet {
  public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();
	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
	Vector3 GetWorldPosition();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }
	float radius = 3.0f;

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	//���x
	Vector3 velocity_;

	//���Ŏ���
	static const int32_t LifeTime = 60 * 5;
	
	//�^�C�}�[
	int32_t deathTimer_ = LifeTime;
	
	//���S�t���O
	bool isDead_ = false;
};