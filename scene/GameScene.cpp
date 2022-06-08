#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include"MathUtility.h"

float PI = 3.1415926;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model;
	delete debugCamera;
}

void GameScene::Initialize() {

	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	debugText = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle = TextureManager::Load("mario.jpg");
	//モデル生成
	model = Model::Create();
	//ワールドトランスフォームの初期化
	worldTransform.Initialize();
	//ビュープロジェクションの初期化
	viewProjection.Initialize();
	//デバックカメラの生成
	debugCamera = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera->GetViewProjection());
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera->GetViewProjection());
	float hen[12][2];
	float hen2[12][2];

	////x,y,z方向のスケーリングを設定
	//worldTransform.scale_ = {1,5,1};

	//Matrix4 matScale;

	//matScale = {
	//  1.0f,0.0f,0.0f,0.0f,
	//  0.0f,1.0f,0.0f,0.0f,
	//  0.0f,0.0f,1.0f,0.0f,
	//  0.0f,0.0f,0.0f,1.0f
	//};

	//matScale.m[0][0] = worldTransform.scale_.x;
	//matScale.m[1][1] = worldTransform.scale_.y;
	//matScale.m[2][2] = worldTransform.scale_.z;

	//worldTransform.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//  0.0f, 0.0f, 1.0f, 0.0f, 
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};
	//
	//worldTransform.matWorld_ *= matScale;

	////行列の転送
	//worldTransform.TransferMatrix();

	//----------------------------------------------
	////x,y,z軸周りの回転角を設定
	//worldTransform.rotation_ = {0.0f,0.0f,0.0f};

	////Z軸回転行列を宣言
	//Matrix4 matRotZ;

	//matRotZ = {
	//  1.0f, 0.0f, 0.0f, 0.0f,
	//  0.0f, 1.0f, 0.0f, 0.0f,
	//  0.0f,0.0f, 1.0f, 0.0f,
	//  0.0f, 0.0f, 0.0f, 1.0f
	//};

	//matRotZ.m[0][0] = cos(worldTransform.rotation_.z);
	//matRotZ.m[0][1] = sin(worldTransform.rotation_.z);
	//matRotZ.m[1][0] = -sin(worldTransform.rotation_.z);
	//matRotZ.m[1][1] = cos(worldTransform.rotation_.z);
	//worldTransform.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f, 
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};
	//worldTransform.matWorld_ *= matRotZ;

	////-----------------------------------------------------------

	//// X軸回転行列を宣言
	//Matrix4 matRotX;

	//matRotX = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};

	//matRotX.m[1][1] = cos(worldTransform.rotation_.x);
	//matRotX.m[2][1] = sin(worldTransform.rotation_.x);
	//matRotX.m[1][2] = -sin(worldTransform.rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform.rotation_.x);
	//worldTransform.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f, 
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};
	//worldTransform.matWorld_ *= matRotX;

	////--------------------------------------------------------
	//// Y軸回転行列を宣言
	//Matrix4 matRotY;

	//matRotY = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};

	//matRotY.m[0][0] = cos(worldTransform.rotation_.y);
	//matRotY.m[2][0] = sin(worldTransform.rotation_.y);
	//matRotY.m[2][0] = -sin(worldTransform.rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform.rotation_.y);
	//worldTransform.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};
	//worldTransform.matWorld_ *= matRotY;

	////行列の転送
	//worldTransform.TransferMatrix();

//-----------------------------------------------------------------------------

	////x,y,z軸周りの回転角を設定
	//worldTransform.rotation_ = {PI / 4, PI / 4, PI / 4};
	////合成用回転行列を宣言
	//Matrix4 matRot;
	////各軸用回転行列を宣言
	//Matrix4 matRotX, matRotY, matRotZ;
	//
	//matRot = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f,1.0f};


	//matRotZ = MathUtility::Matrix4Identity();
	//matRotX = MathUtility::Matrix4Identity();
	//matRotY = MathUtility::Matrix4Identity();
	//

	//matRotZ.m[0][0] = cos(worldTransform.rotation_.z);
	//matRotZ.m[0][1] = sin(worldTransform.rotation_.z);
	//matRotZ.m[1][0] = -sin(worldTransform.rotation_.z);
	//matRotZ.m[1][1] = cos(worldTransform.rotation_.z);

	//matRotX.m[1][1] = cos(worldTransform.rotation_.x);
	//matRotX.m[1][2] = sin(worldTransform.rotation_.x);
	//matRotX.m[2][1] = -sin(worldTransform.rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform.rotation_.x);

	//matRotY.m[0][0] = cos(worldTransform.rotation_.y);
	//matRotY.m[2][0] = sin(worldTransform.rotation_.y);
	//matRotY.m[0][2] = -sin(worldTransform.rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform.rotation_.y);
	//
	////各軸の回転行列を合成
	//matRot *= matRotZ *= matRotX *= matRotY;

	//worldTransform.matWorld_ *= matRot;

	//worldTransform.TransferMatrix();

//-------------------------------------------------------------------------
	//worldTransform.translation_ = {0, 10, 0};

	//Matrix4 matTrans = MathUtility::Matrix4Identity();

	//matTrans.m[3][0] += worldTransform.translation_.x;
	//matTrans.m[3][1] += worldTransform.translation_.y;
	//matTrans.m[3][2] += worldTransform.translation_.z;

	//worldTransform.matWorld_ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//    0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};

	//worldTransform.matWorld_ *= matTrans;

	//worldTransform.TransferMatrix();
	
	worldTransform.scale_ = {5, 5, 5};
	worldTransform.rotation_ = {PI / 4, PI / 4, 0.0f};
	worldTransform.translation_ = {10, 10, 10};

	Matrix4 matScale;
	matScale = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;

	matRot = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matScale.m[0][0] = worldTransform.scale_.x;
	matScale.m[1][1] = worldTransform.scale_.y;
	matScale.m[2][2] = worldTransform.scale_.z;

	matRotZ = MathUtility::Matrix4Identity();
	matRotX = MathUtility::Matrix4Identity();
	matRotY = MathUtility::Matrix4Identity();

	matRotZ.m[0][0] = cos(worldTransform.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform.rotation_.z);

	matRotX.m[1][1] = cos(worldTransform.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform.rotation_.x);

	matRotY.m[0][0] = cos(worldTransform.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform.rotation_.y);

	matTrans.m[3][0] += worldTransform.translation_.x;
	matTrans.m[3][1] += worldTransform.translation_.y;
	matTrans.m[3][2] += worldTransform.translation_.z;

	worldTransform.matWorld_ = {
	  1.0f, 0.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	};

	matRot *= matRotZ *= matRotX *= matRotY;
	worldTransform.matWorld_ *= matScale *= matRot *= matTrans;
	worldTransform.TransferMatrix();
}

void GameScene::Update() {
	//デバックカメラの更新
	debugCamera->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	//モデルカメラを連動
	model->Draw(worldTransform, debugCamera->GetViewProjection(), textureHandle);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	///
	// 3Dモデル描画
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	//for (int i = 0; i < 12; i++) {
	//	// PrimitiveDrawer::GetInstance()->DrawLine3d(hen[i][0], hen[i][1], Vector4(0, 70, 0, 255));
	//	PrimitiveDrawer::GetInstance()->DrawLine3d(
	//	  ten[hen2[i][0]], ten[hen2[i][1]], Vector4(0, 70, 0, 255));
	//}

	// PrimitiveDrawer::GetInstance()->DrawLine3d(box[i % 4], box[(i + 1) % 4], Vector4(0, 70, 0,
	// 255));			//1^4 PrimitiveDrawer::GetInstance()->DrawLine3d(box[i % 4 + 4], box[(i + 1)
	// % 4 + 4], Vector4(0, 70, 0, 255));	//5^8 PrimitiveDrawer::GetInstance()->DrawLine3d(box[i %
	// 4], box[i % 4 +4], Vector4(0, 70, 0, 255));				//縦

	/*
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(5, 0, 0), Vector4(255, 0,
	0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 0), Vector3(5, 5, 0),
	Vector4(255, 0, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 0),
	Vector3(0, 5, 0), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 5, 0), Vector3(0, 0, 0), Vector4(255, 0,
	0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 5), Vector3(0, 5, 5),
	Vector4(255, 0, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 5),
	Vector3(5, 0, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 5), Vector3(5, 5, 5), Vector4(255, 0,
	0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 5), Vector3(0, 5, 5),
	Vector4(255, 0, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0),
	Vector3(0, 0, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 0), Vector3(5, 0, 5), Vector4(255, 0,
	0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 0), Vector3(5, 5, 5),
	Vector4(255, 0, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 5, 0),
	Vector3(0, 5, 5), Vector4(255, 0, 0, 255));*/

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}