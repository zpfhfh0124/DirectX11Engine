#pragma once
#include <Windows.h>

class Window
{
public:
	bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
	void Destroy();

	HWND GetHWND() const { return m_hWnd; }

	bool ProcessMessage();

private:
	HWND m_hWnd = nullptr;
public:

	Window() = default;
};
