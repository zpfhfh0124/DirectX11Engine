#include "Application.h"

Application::Application(HINSTANCE hInstance) : m_hInstance(hInstance)
{
}

bool Application::Initialize(HINSTANCE hInstance, int width, int height)
{
	// 에러메시지
	if (!m_window.Create(m_hInstance, width, height, L"DX11 Engine")) 
		return false;
	
	if (!m_gfx.Initialize(m_window.GetHWND(), width, height))
		return false;

	if (!m_renderer.Initialize(&m_gfx, width, height))
		return false;

	// 삼각형 mesh 하나 생성
	vector<VertexPC> vertices = {
		{ { 0.0f, 0.5f, 0.0f }, {1, 0, 0}},
		{ { 0.5f, -0.5f, 0.0f }, {0, 1, 0}},
		{ { -0.5f, -0.5f, 0.0f }, {0, 0, 1}},
	};
	vector<uint32_t> indices = { 0,1,2 };

	if (!m_triangle.Initialize(&m_gfx, vertices, indices))
		return false;

	m_running = true;
	return true;
}

int Application::Run()
{
	while (m_running)
	{
		if (!m_window.ProcessMessage())
			break;

		// Update/Render
		Render();
	}

	return 0;
}

void Application::Update(float deltaTime)
{
}

void Application::Render()
{
	m_renderer.BeginFrame();

	// 메쉬 Draw
	m_renderer.DrawMesh(m_triangle);

	m_renderer.EndFrame();
}
