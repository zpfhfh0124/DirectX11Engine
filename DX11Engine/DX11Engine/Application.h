#pragma once
#include "Window.h"
#include "GraphicsDevice.h"
#include "Renderer.h"
#include "Transform.h"

class Application
{
public:
	Application(HINSTANCE hInstance);
	bool Initialize(int width, int height);
	int Run();

private:
	HINSTANCE m_hInstance;
	Window m_window;
	GraphicsDevice m_gfx;
	Renderer m_renderer;
	Mesh m_triangle; // 삼각형 메쉬
	Transform m_triangleTransform;
	bool m_running = false;

	// 시간 계산
	double m_timeScale = 0.0;
	double m_prevTime = 0.0;

	void Update(float deltaTime);
	void Render();
	
};

