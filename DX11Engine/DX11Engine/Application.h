#pragma once
#include "Window.h"
#include "GraphicsDevice.h"
#include "Renderer.h"

class Application
{
public:
	Application(HINSTANCE hInstance);
	bool Initialize(HINSTANCE hInstance, int width, int height);
	int Run();

private:
	HINSTANCE m_hInstance;
	Window m_window;
	GraphicsDevice m_gfx;
	Renderer m_renderer;
	Mesh m_triangle; // 삼각형 메쉬
	bool m_running = false;

	void Update(float deltaTime);
	void Render();
	
};

