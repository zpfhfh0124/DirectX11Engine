#include "ThirdPersonCamera.h"
#include "Transform.h"

ThirdPersonCamera::ThirdPersonCamera() {}

void ThirdPersonCamera::SetTarget(Transform* target) { m_target = target; }

void ThirdPersonCamera::SetOffset(float height, float distance) { m_height = height; }

void ThirdPersonCamera::SetSensitivity(float sens) { m_sensitivity = sens; }

void ThirdPersonCamera::SetPitchLimit(float minPitchRad, float maxPitchRad) { m_minPitch = minPitchRad; m_maxPitch = maxPitchRad; }

void ThirdPersonCamera::Update(float deltaTime, float mouseDeltaX, float mouseDeltaY)
{
	if (!m_target) return;

	// yaw/pitch 누적
	m_yaw += mouseDeltaX * m_sensitivity;
	m_pitch += mouseDeltaY * m_sensitivity;

	m_pitch = clamp(m_pitch, m_minPitch, m_maxPitch);

	// 타겟 위치
	XMMATRIX targetWorld = m_target->GetWorldMatrix();
	XMFLOAT3 targetPos;
	XMStoreFloat3(&targetPos, targetWorld.r[3]); // translation

	// 카메라 오프셋 (타겟 기준) : 뒤로 distance, 위로 height
	// 기본 오프셋 : (0, height, -distance)
	XMVECTOR localOffset = XMVectorSet(0.0f, m_height, -m_distance, 0.0f);

	// yaw/patch 회전 적용
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0.0f);
	XMVECTOR rotatedOffset = XMVector3TransformCoord(localOffset, rot);

	XMVECTOR tp = XMLoadFloat3(&targetPos);
	XMVECTOR camPos = tp + rotatedOffset;

	XMStoreFloat3(&m_position, camPos);
}

XMMATRIX ThirdPersonCamera::GetView() const
{
	// 카메라는 타겟을 바라봄 ( 목 높이 정도를 바라보면 자연스러움 )
	// 타겟 포인터가 없어도 안전하게 처리
	if (!m_target)
	{
		XMVECTOR pos = XMLoadFloat3(&m_position);
		XMVECTOR forward = XMVectorSet(0, 0, 1, 0);
		XMVECTOR up = XMLoadFloat3(&m_up);
		return XMMatrixLookToLH(pos, forward, up);
	}

	XMMATRIX targetWorld = m_target->GetWorldMatrix();
	XMFLOAT3 targetPos;
	XMStoreFloat3(&targetPos, targetWorld.r[3]);

	XMVECTOR eye = XMLoadFloat3(&m_position);
	XMVECTOR at = XMLoadFloat3(&targetPos) + XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR up = XMLoadFloat3(&m_up);

	return XMMatrixLookAtLH(eye, at, up);
}
