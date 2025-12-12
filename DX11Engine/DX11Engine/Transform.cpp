#include "Transform.h"
using namespace DirectX;

Transform::Transform()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale	   = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
}

void Transform::SetRotation(float pitch, float yaw, float roll)
{
	m_rotation = XMFLOAT3(pitch, yaw, roll);
}

void Transform::SetScale(float x, float y, float z)
{
	m_scale = XMFLOAT3(x, y, z);
}

XMMATRIX Transform::GetWorldMatrix() const
{
	XMVECTOR pos = XMLoadFloat3(&m_position);
	XMVECTOR rot = XMLoadFloat3(&m_rotation);
	XMVECTOR scl = XMLoadFloat3(&m_scale);

	XMMATRIX S = XMMatrixScalingFromVector(scl);
	XMMATRIX R = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX T = XMMatrixTranslationFromVector(pos);

	return S * R * T;
}