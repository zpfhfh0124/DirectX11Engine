#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

class GraphicsDevice
{
public:
	bool Initialize(HWND hwnd, int width, int height);
	void BeginFrame(float r, float g, float b, float a);
	void endFrame();

private:
	Microsoft::WRL::ComPtr<ID3D11Device>			m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_dsv;
};

