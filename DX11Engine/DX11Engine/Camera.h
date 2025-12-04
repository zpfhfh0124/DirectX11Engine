#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3& vector);
	void LookAt(float x, float y, float z);
	void LookAt(XMFLOAT3& vector);
	void SetLens(float fovY, float aspect, float zn, float zf);

	XMMATRIX GetView() const;
	XMMATRIX GetProj() const;

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_target;
	XMFLOAT3 m_up;

	float m_fovY;
	float m_aspect;
	float m_nearZ;
	float m_farZ;
};

