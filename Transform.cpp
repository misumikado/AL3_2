#include "Transform.h"
#include "MathUtility.h"
#include <math.h>

#define PI 3.141592

namespace affinMove {
void Scale(WorldTransform &worldTransform_, float sx, float sy, float sz) { //スケーリング

	//スケーリングーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	
	// X,Y,Z方向のスケーリング
	worldTransform_.scale_ = {sx, sy, sz};
	//スケーリング行列を宣言
	Matrix4 matScale;
	//スケーリング倍率を行列を宣言
	matScale = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matScale;

	//行列の転送
	worldTransform_.TransferMatrix();
}
//回転ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
void Rot(WorldTransform &worldTransform_) { //回転

	// X,Y,Z方向の回転
	
	//回転行列を宣言
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	
	//回転倍率を行列を宣言
	matRot = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	matRotZ = MathUtility ::Matrix4Identity();
	matRotX = MathUtility ::Matrix4Identity();
	matRotY = MathUtility ::Matrix4Identity();
	
	// Z軸回転の各要素
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	
	// X軸回転の各要素
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	
	// Y軸回転の各要素
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	//各軸用回転行列を宣言
	matRot *= matRotZ *= matRotX *= matRotY;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matRot;

	//行列の転送
	worldTransform_.TransferMatrix();
}

//平行移動--------------------------------------------------------------------------------------
void Trans(WorldTransform &worldTransform_) { //移動

	// X,Y,Z方向の平行移動
	
	//平行移動行列を宣言
	Matrix4 matTrans;
	//平行移動を行列を宣言
	matTrans = MathUtility ::Matrix4Identity();

	matTrans.m[3][0] += worldTransform_.translation_.x;
	matTrans.m[3][1] += worldTransform_.translation_.y;
	matTrans.m[3][2] += worldTransform_.translation_.z;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matTrans;
	//行列の転送
	worldTransform_.TransferMatrix();
}
//合成ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
void Transform( WorldTransform &worldTransform_) {

	//スケーリング行列を宣言
	Matrix4 matScale;
	
	//回転行列を宣言
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	
	//平行移動行列を宣言
	Matrix4 matTrans;

	matScale = MathUtility ::Matrix4Identity();
	matRot = MathUtility ::Matrix4Identity();
	matRotX = MathUtility ::Matrix4Identity();
	matRotY = MathUtility ::Matrix4Identity();
	matRotZ = MathUtility ::Matrix4Identity();
	matTrans = MathUtility ::Matrix4Identity();

	//倍率
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	
	// Z軸回転の各要素
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	
	// X軸回転の各要素
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	
	// Y軸回転の各要素
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	
	//平行移動
	matTrans.m[3][0] += worldTransform_.translation_.x;
	matTrans.m[3][1] += worldTransform_.translation_.y;
	matTrans.m[3][2] += worldTransform_.translation_.z;

	//各軸用回転行列を宣言
	matRot *= matRotZ *= matRotX *= matRotY;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ = matScale *= matRot *= matTrans;
}
} // namespace myApp
