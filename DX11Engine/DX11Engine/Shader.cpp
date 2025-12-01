#include "Shader.h"
#include "GraphicsDevice.h"

bool Shader::Initialize(GraphicsDevice* device, const wstring& vsPath, const wstring& psPath)
{
	ID3D11Device* d3d = device->GetDevice();
	HRESULT hr = S_OK;

	// vertex shader 컴파일
	ComPtr<ID3DBlob> vsBlob;
	hr = CompileShaderFromFile(vsPath, "VSMain", "vs_5_0", vsBlob.GetAddressOf());
	if (FAILED(hr))
		return false;

	hr = d3d->CreateVertexShader(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf());
	if (FAILED(hr))
		return false;

	// pixel shader 컴파일
	ComPtr<ID3DBlob> psBlob;
	hr = CompileShaderFromFile(psPath, "PSMain", "ps_5_0", psBlob.GetAddressOf());
	if (FAILED(hr))
		return false;

	hr = d3d->CreatePixelShader(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		m_pixelShader.GetAddressOf());
	if (FAILED(hr))
		return false;

	// InputLayout 생성 (VertexPC 기준)
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = d3d->CreateInputLayout(
		layout,
		_countof(layout),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		m_inputLayout.GetAddressOf());
	if (FAILED(hr))
		return false;

	return true;
}

void Shader::Bind(GraphicsDevice* device)
{
	ID3D11DeviceContext* ctx = device->GetContext();

	ctx->IASetInputLayout(m_inputLayout.Get());
	ctx->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	ctx->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}

HRESULT Shader::CompileShaderFromFile(const wstring& filePath, const char* entryPoint, const char* target, ID3DBlob** outBlob)
{
	DWORD compileFlags = 0;
	// 디버깅 전용 플래그
#if defined(_DEBUG)
	compileFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	HRESULT hr = D3DCompileFromFile(
		filePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		target,
		compileFlags,
		0,
		shaderBlob.GetAddressOf(),
		errorBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (errorBlob)
		{
			// 에러 메시지 출력
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}

		return hr;
	}

	*outBlob = shaderBlob.Detach(); // 호출자에게 넘김
	return S_OK;
}

