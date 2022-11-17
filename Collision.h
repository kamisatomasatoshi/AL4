#pragma once

#include "CollisionPrimitive.h"

//�����蔻��w���p�[�N���X

class Collision
{
public:
	//<summary>
	//���敽�ʂ̓����蔻��
	//<summary>
	//<param name="sphere">��</param>
	//<param name="plane">����</param>
	//<param name="inter">����(���ʏ�̍ŋߐړ_)</param>
	//<returns>�������Ă��邩�ۂ�</returns>

	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);

	///
	///�_�ƎO�p�`�̍ŋߐړ_�����߂�
	/// 
	/// <pragama name = "point"�_</param>
	/// <pragama name = "triangle"�O�p�`</param>
	/// <pragama name = "closest"�ŋߐړ_(�o�͗p)</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);

	// <summary>
		//���Ɩ@���t���O�p�`�̓����蔻��
		//<summary>
		//<param name="sphere">��</param>
		//<param name="triangle">�O�p�`</param>
		//<param name="inter">����(�O�p�`��̍ŋߐړ_)</param>
		//<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);

	//���C�ƕ��ʂ̓����蔻��
	//<summary>
	//<param name="lay">���C</param>
	//<param name="plane">����</param>
	//<param name="inter">����(�o�͗p)</param>
	//<param name="inter">����(�o�͗p)</param>
	//<returns>�������Ă��邩�ۂ�</returns>

	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

};
