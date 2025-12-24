#pragma once
#include <DirectXMath.h>
#include <algorithm>

using namespace DirectX;
using namespace std;

class Transform;

class ThirdPersonCamera
{
public:
	ThirdPersonCamera();

	void SetTarget(Transform* target);
	void SetOffset(float height, float distance);
	void SetSensitivity(float sens);
	void SetPitchLimit(float minPitchRad, float maxPitchRad);

	void Update(float deltaTime, float mouseDeltaX, float mouseDeltaY);

	XMMATRIX GetView() const;

	XMFLOAT3 GetPosition() const { return m_position; }
	float GetYaw() const { return m_yaw; }
	float GetPitch() const { return m_pitch; }
private:
	Transform* m_target = nullptr;

	float m_height = 1.0f;
	float m_distance = 4.0f;

	float m_sensitivity = 0.0035f; // 마우스 감도
	float m_yaw = 0.0f;			   // 좌우 회전
	float m_pitch = 0.2f;		   // 상하 회전

	float m_minPitch = -1.2f;
	float m_maxPitch = 1.2f;

	XMFLOAT3 m_position = { 0,0,0 };
	XMFLOAT3 m_up = { 0,1,0 };
};

