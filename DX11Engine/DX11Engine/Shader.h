#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

using namespace std;

class GraphicsDevice;

class Shader
{
public:
	bool Initialize(GraphicsDevice* device,
		const wstring& vsPath,
		const wstring& psPath);

	void Bind(GraphicsDevice* device);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_inputLayout;
};

