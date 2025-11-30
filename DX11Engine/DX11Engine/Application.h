#pragma once
#include "Window.h"
#include "GraphicsDevice.h"

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
	bool m_running = false;

	void Update(float deltaTime);
	void Render();
	
};

