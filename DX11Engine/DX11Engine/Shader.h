#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

using namespace std;
using namespace Microsoft::WRL;

class GraphicsDevice;

class Shader
{
public:
	bool Initialize(GraphicsDevice* device,
		const wstring& vsPath,
		const wstring& psPath);

	void Bind(GraphicsDevice* device);

	HRESULT CompileShaderFromFile(const wstring& filePath,
		const char* entryPoint, const char* target, ID3DBlob** outBlob);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_inputLayout;
};

