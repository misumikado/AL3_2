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
	//worldTransform_.Initialize();
	worldTransforms_[100].Initialize();

	//カメラの視点座標を設定
	//viewProjection_.eye = {0.0f, 0.0f,0.0f};
	//カメラの注視座標を設定
	//viewProjection_.target = {10.0f, 0.0f, 0.0f};
	
	//カメラ上方向のベクトルを設定(右上45度指定)
	//viewProjection_.up = {cosf(PI / 4.0f), sinf(PI / 4.0f), 0.0f};

	//カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = 10*PI/180;

	//アスペクト比を設定
	viewProjection_.aspectRatio = 1.0f;

	//ニアクリップ距離を設定
	viewProjection_.nearZ = 52.0f;

	//ファークリップ距離を設定
	viewProjection_.farZ = 53.0f;


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


	//範囲forで全てのワールドトランスフォーム順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {

		worldTransform.Initialize();
		float rotvalue = rotDist(engine);
		float posX = posDist(engine);
		float posY = posDist(engine);
		float posZ = posDist(engine);

		//	// x,y,z方向のスケーリング設定
		worldTransform.scale_ = {1.0f, 1.0f, 1.0f};
		//	// x,y,z軸周りの回転角を設定
		worldTransform.rotation_ = {rotvalue, rotvalue, rotvalue};
		//	// x,y,z軸周りの平行移動を設定
		worldTransform.translation_ = {posX, posY, posZ};
		//	//スケーリング・回転・平行移動を合成した行列を計算してワールドトランスフォームに代入
		//
		affinMove::Transform(worldTransform);
		//
		worldTransform.TransferMatrix();
	}
};

void GameScene::Update() {
	//デバックカメラの更新
	debugCamera_->Update();

	Vector3 move = {0.0f, 0.0f, 0.0f};

	//視点の移動速さ
	const float kEyeSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_W)) {
		move.z += kEyeSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.z -= kEyeSpeed;
	}
	//視点移動(ベクトルの加算)
	viewProjection_.eye += move;
	//-------------------------------------

	//視点の移動速さ
	const float kTargetSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x += kTargetSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x -= kTargetSpeed;
	}

	//視点移動(ベクトルの加算)
	viewProjection_.target += move;

	//上方向回転処理
	{
		//上方向の回転速さ[ラジアン/frame]
		const float kUpRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_SPACE)) {
			viewAngle += kUpRotSpeed;
			//2πを超えたら0に戻す
			viewAngle = fmodf(viewAngle, PI * 2.0f);
		}
		//上方向ベクトルを計算(半径1円周上の座標)
		viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバッグ用表示
		debugText_->SetPos(50, 90);
		debugText_->Printf(
		  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);

	}

	//FoV変更処理
	//{
	//	//上キーで視野角が広がる
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.fovAngleY += 0.01f;
	//		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY,PI);
	//	} else if (input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.fovAngleY -= 0.01f;
	//		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY,0.01f);
	//	}
	//	viewProjection_.UpdateMatrix();

	//	//デバッグ用表示
	//	debugText_->SetPos(50, 110);
	//	debugText_->Printf("fovAngleY(Degree):%f",viewProjection_.fovAngleY);
	//}

	//クリップ距離変更処理
	{
		//上下キーでニアクリップを増減
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.nearZ += 0.01f;
		} else if (input_->PushKey(DIK_DOWN)) {
			viewProjection_.nearZ -= 0.01f;
		}

		//行列の再計算
		viewProjection_.UpdateMatrix();
		//デバッグ用表示
		debugText_->SetPos(50, 130);
		debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
	}


	//行列の再計算
	viewProjection_.UpdateMatrix();

	//デバッグ用表示
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "target(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
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
	 for (WorldTransform& worldTransform : worldTransforms_) {
		//model ->Draw(worldTransform,  viewProjection_, textureHandle);
		model_->Draw(worldTransform, viewProjection_, textureHandle_);

		//model_->Draw(worldTransform, debugCamera_->GetViewProjection(), textureHandle_);
	 }

	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

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