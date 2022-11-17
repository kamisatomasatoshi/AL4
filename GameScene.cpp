﻿#include "GameScene.h"
#include "Collision.h"
#include <sstream>
#include <iomanip>
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	object3d->Update();


	//弾の初期化
	sphere.center = XMVectorSet(0, 2, 0, 1);//中心
	//半径
	sphere.radius = 1.0f;

	//平面の初期化
	plane.normal = XMVectorSet(0, 1, 0, 0);//法線ベクトル
	plane.distance = 0.0f;//原点からの距離

	//三角形の初期値を設定
	triangle.p0 = XMVectorSet(-1.0f, 0, -1.0f, 1);
	triangle.p1 = XMVectorSet(-1.0f, 0, +1.0f, 1);
	triangle.p2 = XMVectorSet(+1.0f, 0, -1.0f, 1);
	triangle.normal = XMVectorSet( 0.0f, 1.0,0.0f, 0);

	//レイの初期設定を設定
	ray.start = XMVectorSet(0, 1, 0, 1);
	ray.dir = XMVectorSet(0, -1, 0, 0);

}

void GameScene::Update()
{
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		XMFLOAT3 position = object3d->GetPosition();

		// 移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		object3d->SetPosition(position);
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}


	////球移動
	//{
	//	//Y軸方向移動
	//	XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
	//	if (input->PushKey(DIK_NUMPAD8))
	//	{
	//		sphere.center += moveY;
	//	}
	//	else if (input->PushKey(DIK_NUMPAD8))
	//	{
	//		sphere.center -= moveY;
	//	}
	//	//X軸方向移動
	//	XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
	//	if (input->PushKey(DIK_NUMPAD6))
	//	{
	//		sphere.center += moveX;
	//	}
	//	else if (input->PushKey(DIK_NUMPAD4))
	//	{
	//		sphere.center -= moveX;
	//	}
	//}
	
	//レイ操作
	{
		XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
		if (input->PushKey(DIK_NUMPAD8))
		{
			ray.start += moveZ;
		}
		else if (input->PushKey(DIK_NUMPAD2))
		{
			ray.start -= moveZ;
		}

		XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
		if (input->PushKey(DIK_NUMPAD6))
		{
			ray.start += moveX;
		}
		else if (input->PushKey(DIK_NUMPAD4))
		{
			ray.start -= moveX;
		}
	} 

	std::ostringstream raystr;
	raystr << "lay.start("
		<< std::fixed << std::setprecision(2)
		<< ray.start.m128_f32[0] << ","
		<< ray.start.m128_f32[1] << ","
		<< ray.start.m128_f32[2] << ")";

	debugText.Print(raystr.str(), 50, 180, 1.0f);
	//stringstreamで変数の値を埋め込んで整形する
	//std::ostringstream sqherestr;
	//sqherestr << "Sqhere:("
	//	<< std::fixed << std::setprecision(2)//少数第２まで
	//	<< sphere.center.m128_f32[0] << ","//x
	//	<< sphere.center.m128_f32[1] << ","//y
	//	<< sphere.center.m128_f32[2] << ")";//z
	//debugText.Print(sqherestr.str(), 50, 180, 1.0f);
	//当たり判定
	//bool hit = Collision::CheckSphere2Plane(sphere, plane);
	//if (hit)
	//{
	//	debugText.Print("HIT", 50, 200, 1.0f);
	//	//stringstreamリセット,交点座標を埋め込む
	//	sqherestr.str("");
	//	sqherestr.clear();
	//	sqherestr << "("
	//		<< std::fixed << std::setprecision(2)//少数第２まで
	//		<< sphere.center.m128_f32[0] << ","//x
	//		<< sphere.center.m128_f32[1] << ","//y
	//		<< sphere.center.m128_f32[2] << ")";//z
	//	debugText.Print(sqherestr.str(), 50, 220, 1.0f);
	//}



	//XMVECTOR inter;
	//bool hit = Collision::CheckSphere2Triangle(sphere, triangle, &inter);
	//if (hit) 
	//{
	//	debugText.Print("HIT", 50, 200, 1.0f);
	//	sqherestr.str("");
	//	sqherestr.clear();
	//	sqherestr << "("
	//		<< std::fixed << std::setprecision(2)//少数第２まで
	//		<< sphere.center.m128_f32[0] << ","//x
	//		<< sphere.center.m128_f32[1] << ","//y
	//		<< sphere.center.m128_f32[2] << ")";//z
	//	debugText.Print(sqherestr.str(), 50, 220, 1.0f);
	//}

	object3d->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

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
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	object3d->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
