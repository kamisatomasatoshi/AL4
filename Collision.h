#pragma once

#include "CollisionPrimitive.h"

//当たり判定ヘルパークラス

class Collision
{
public:
	//<summary>
	//球よ平面の当たり判定
	//<summary>
	//<param name="sphere">球</param>
	//<param name="plane">平面</param>
	//<param name="inter">交差(平面上の最近接点)</param>
	//<returns>交差しているか否か</returns>

	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);

	///
	///点と三角形の最近接点を求める
	/// 
	/// <pragama name = "point"点</param>
	/// <pragama name = "triangle"三角形</param>
	/// <pragama name = "closest"最近接点(出力用)</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);

	// <summary>
		//球と法線付き三角形の当たり判定
		//<summary>
		//<param name="sphere">球</param>
		//<param name="triangle">三角形</param>
		//<param name="inter">交差(三角形上の最近接点)</param>
		//<returns>交差しているか否か</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);

};
