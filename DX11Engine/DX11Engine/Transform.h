#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	Transform();

	void SetPosition(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	void SetScale(float x, float y, float z);

	XMMATRIX GetWorldMatrix() const;

	XMFLOAT3& Position() { return m_position; }
	XMFLOAT3& Rotation() { return m_rotation; }
	XMFLOAT3& Scale() { return m_scale; }

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_scale;
};

