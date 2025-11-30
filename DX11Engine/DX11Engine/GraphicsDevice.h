#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <string>

class GraphicsDevice
{
public:
	bool Initialize(HWND hwnd, int width, int height);
	void BeginFrame(float r, float g, float b, float a);
	void EndFrame();

	ID3D11Device*		 GetDevice() const { return m_device.Get(); }
	ID3D11DeviceContext* GetContext() const { return m_context.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11Device>			m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_dsv;
};

