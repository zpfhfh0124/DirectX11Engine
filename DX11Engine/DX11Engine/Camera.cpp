#include "Camera.h"

Camera::Camera()
{
	m_position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	m_target   = XMFLOAT3(0.0f, 0.0f,  0.0f);
	m_up	   = XMFLOAT3(0.0f, 1.0f,  0.0f);

	m_fovY = XM_PIDIV4; // PI/4 = 45도
	m_aspect = 16.0f / 9.0f; // 종횡비
	// 클리핑 영역
	m_nearZ = 0.1f;
	m_farZ = 1000.0f;
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
}

void Camera::SetPosition(XMFLOAT3& vector)
{
	m_position = vector;
}

void Camera::LookAt(float x, float y, float z)
{
	m_target = XMFLOAT3(x, y, z);
}

void Camera::LookAt(XMFLOAT3& vector)
{
	m_target = vector;
}

void Camera::SetLens(float fovY, float aspect, float zn, float zf)
{
	m_fovY = fovY;
	m_aspect = aspect;
	m_nearZ = zn;
	m_farZ = zf;
}

XMMATRIX Camera::GetView() const
{
	XMVECTOR pos = XMLoadFloat3(&m_position);
	XMVECTOR tgt = XMLoadFloat3(&m_target);
	XMVECTOR up = XMLoadFloat3(&m_up);

	// 월드 공간 -> 뷰 공간 변환
	return XMMatrixLookAtLH(pos, tgt, up);
}

XMMATRIX Camera::GetProj() const
{
	return XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearZ, m_farZ);
}


