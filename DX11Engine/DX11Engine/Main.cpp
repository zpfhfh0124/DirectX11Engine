#pragma once
#include <Windows.h>
#include "Application.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow) 
{
	Application app(hInstance);
	if (!app.Initialize(hInstance, 1280, 720))
		return -1;

	return app.Run();
}