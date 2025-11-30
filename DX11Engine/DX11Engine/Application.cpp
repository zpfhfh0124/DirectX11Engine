#include "Application.h"

Application::Application(HINSTANCE hInstance) : m_hInstance(hInstance)
{
}

bool Application::Initialize(HINSTANCE hInstance, int width, int height)
{
	// 테스트용 에러메시지
	if (!m_window.Create(m_hInstance, width, height, L"DX11 Engine")) 
	{
		MessageBox(nullptr, L"Window::Create 실패", L"Error", MB_OK);
		return false;
	}

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
	}

	return 0;
}

void Application::Update(float deltaTime)
{
}

void Application::Render()
{
}
