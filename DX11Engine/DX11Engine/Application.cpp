#include "Application.h"

Application::Application(HINSTANCE hInstance) : m_hInstance(hInstance)
{
}

bool Application::Initialize(int width, int height)
{
	// 에러메시지
	if (!m_window.Create(m_hInstance, width, height, L"DX11 Engine")) 
		return false;
	
	if (!m_gfx.Initialize(m_window.GetHWND(), width, height))
		return false;

	if (!m_renderer.Initialize(&m_gfx, width, height))
		return false;

	// 고정밀 타이머 초기화
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	m_timeScale = 1.0 / double(freq.QuadPart);

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	m_prevTime = double(now.QuadPart) * m_timeScale;

	// 삼각형 mesh 하나 생성
	vector<VertexPC> vertices = {
		{ { 0.0f, 0.5f, 0.0f }, {1, 0, 0}},
		{ { 0.5f, -0.5f, 0.0f }, {0, 1, 0}},
		{ { -0.5f, -0.5f, 0.0f }, {0, 0, 1}},
	};
	vector<uint32_t> indices = { 0,1,2 };

	if (!m_triangle.Initialize(&m_gfx, vertices, indices))
		return false;

	// Transform 기본값
	m_triangleTransform.SetPosition(0.0f, 0.0f, 0.0f);
	m_triangleTransform.SetScale(1.0f, 1.0f, 1.0f);
	m_triangleTransform.SetRotation(0.0f, 0.0f, 0.0f);

	m_running = true;
	return true;
}

int Application::Run()
{
	while (m_running)
	{
		if (!m_window.ProcessMessage())
			break;

		// deltaTime 계산
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		double current = double(now.QuadPart) * m_timeScale;

		float deltaTime = (float)(current - m_prevTime);
		m_prevTime = current;

		// Update/Render
		Update(deltaTime);
		Render();
	}

	return 0;
}

void Application::Update(float deltaTime)
{
	static float angle = 0.0f;
	angle += 0.01f; // 프레임마다 조금씩 회전 (라디안)

	// pitch, yaw, roll 순서 (x, y, z)
	m_triangleTransform.SetRotation(0.0f, angle, 0.0f);
}

void Application::Render()
{
	m_renderer.BeginFrame();

	// 메쉬 Draw
	XMMATRIX world = m_triangleTransform.GetWorldMatrix();
	m_renderer.DrawMesh(m_triangle, world);

	m_renderer.EndFrame();
}
