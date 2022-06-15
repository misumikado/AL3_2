#include "GameScene.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

float PI = 3.1415926;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	//モデル生成
	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	// worldTransform_.Initialize();
	
	//キャラクターの大元
	worldTransforms_[PartId::kRoot].Initialize();
	//脊椎
	worldTransforms_[PartId::kSpine].Initialize();
	worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
	worldTransforms_[PartId::kSpine].translation_ = {0.0f, 4.5f, 0.0f};

	//上半身
	//胸
	worldTransforms_[PartId::kChest].Initialize();
	worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kChest].translation_ = {0, 0, 0};

	//頭
	worldTransforms_[PartId::kHead].Initialize();
	worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kHead].translation_ = {0, 2.5f, 0};

	//左腕
	worldTransforms_[PartId::kArmL].Initialize();
	worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmL].translation_ = {-2.5f, 0, 0};

	//右腕
	worldTransforms_[PartId::kArmR].Initialize();
	worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmR].translation_ = {2.5f, 0, 0};

	//下半身
	//尻
	worldTransforms_[PartId::kHip].Initialize();
	worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kHip].translation_ = {0, -2.5f, 0};

	//左足
	worldTransforms_[PartId::kLegL].Initialize();
	worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegL].translation_ = {-2.5f, -2.5f, 0};

	//右足
	worldTransforms_[PartId::kLegR].Initialize();
	worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegR].translation_ = {2.5f, -2.5f, 0};

	//カメラの視点座標を設定
	// viewProjection_.eye = {0.0f, 0.0f,0.0f};
	//カメラの注視座標を設定
	// viewProjection_.target = {10.0f, 0.0f, 0.0f};

	//カメラ上方向のベクトルを設定(右上45度指定)
	// viewProjection_.up = {cosf(PI / 4.0f), sinf(PI / 4.0f), 0.0f};

	//カメラ垂直方向視野角を設定
	// viewProjection_.fovAngleY = 10*PI/180;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	// AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//乱数シード生成期
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0, 360);
	// r乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
};

void GameScene::Update() {
	//デバックカメラの更新
	debugCamera_->Update();

	//行列の再計算
	viewProjection_.UpdateMatrix();
	Vector3 move = {0.0f, 0.0f, 0.0f};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	//親
	worldTransforms_[PartId::kRoot].translation_ += move;
	affinMove::Translate(worldTransforms_[kRoot]);
	worldTransforms_[0].TransferMatrix();

	//子の更新
	for (int i = 1; i < 9; i++) {
		affinMove::Transform(worldTransforms_[i]);
		worldTransforms_[i].matWorld_ *= worldTransforms_[i].parent_->matWorld_;
		worldTransforms_[i].TransferMatrix();
	}
	//上半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			worldTransforms_[PartId::kChest].rotation_.y += 0.1f;
		} else if (input_->PushKey(DIK_I)) {
			worldTransforms_[PartId::kChest].rotation_.y -= 0.1f;
		}
	}
	//下半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			worldTransforms_[PartId::kHip].rotation_.y += 0.1f;
		} else if (input_->PushKey(DIK_K)) {
			worldTransforms_[PartId::kHip].rotation_.y -= 0.1f;
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>

	//ここに3Dオブジェクトの描画処理を追加できる
	// model ->Draw(worldTransform,  viewProjection_, textureHandle);
	for (int i = 2; i < 9; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

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
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}