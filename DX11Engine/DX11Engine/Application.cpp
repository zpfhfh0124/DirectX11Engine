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
	m_gfx.BeginFrame(1.0f, 1.0f, 1.0f, 1.0f);

	// 메쉬 Draw

	m_gfx.EndFrame();
}
