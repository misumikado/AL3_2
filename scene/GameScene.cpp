#include "GameScene.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>
#include "Player.h"

float PI = 3.1415926;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete player_;
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

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_,textureHandle_);

	//ワールドトランスフォームの初期化
	// worldTransform_.Initialize();
	
	
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
//#ifdef _DEBUG
//	if (input_->TriggerKey(DIK_J)) {
//		isDebugCameraActive_ = true;
//	}
//#endif 
//
//	if (isDebugCameraActive_) {
//		//デバックカメラの更新
//		debugCamera_->Update();
//		viewProjection_.matView = ;
//		viewProjection_.matProjection = ;
//		
//	}
	//行列の再計算
	viewProjection_.UpdateMatrix();

	//自キャラの更新
	player_->Update();

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
	player_->Draw(viewProjection_);
	
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