#include "Renderer.h"
#include "GraphicsDevice.h"
#include "GraphicsCommon.h"

using namespace DirectX;

bool Renderer::Initialize(GraphicsDevice* device, int width, int height)
{
	m_device = device;

	// 카메라 기본 세팅
	float aspect = static_cast<float>(width) / height;
	m_camera = Camera();
	m_camera.SetLens(XM_PIDIV4, aspect, 0.1f, 1000.0f);
	m_camera.SetPosition(0.0f, 0.0f, -5.0f);
	m_camera.LookAt(0.f, 0.f, 0.f);

	// 셰이더
	m_basicShader = make_unique<Shader>();
	if (!m_basicShader->Initialize(device,
		L"Shaders/BasicVS.hlsl", L"Shaders/BasicPS.hlsl")) 
	{
		return false;
	}

	// 상수 버퍼
	D3D11_BUFFER_DESC cbDesc{};
	cbDesc.BindFlags	  = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth	  = sizeof(MatrixBufferData);
	cbDesc.Usage		  = D3D11_USAGE_DYNAMIC;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = m_device->GetDevice()->CreateBuffer(&cbDesc, nullptr, m_matrixBuffer.GetAddressOf());
	if (FAILED(hr))
		return false;

	return true;
}

void Renderer::BeginFrame()
{
	m_device->BeginFrame(0.1f, 0.1f, 0.1f, 1.0f);
}

void Renderer::DrawMesh(const Mesh& mesh)
{
	auto ctx = m_device->GetContext();

	// 월드/뷰/프로젝션 행렬 조합
	XMMATRIX world = XMMatrixIdentity(); // 단위 행렬
	XMMATRIX view = m_camera.GetView();
	XMMATRIX proj = m_camera.GetProj();
	XMMATRIX wvp = world * view * proj;

	MatrixBufferData data{};
	data.worldViewProj = XMMatrixTranspose(wvp); // HLSL column-major 맞추기 위해 transpose

	// 상수 버퍼에 쓰기
	D3D11_MAPPED_SUBRESOURCE mapped{};
	if (SUCCEEDED(ctx->Map(m_matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
	{
		memcpy(mapped.pData, &data, sizeof(MatrixBufferData));
		ctx->Unmap(m_matrixBuffer.Get(), 0);
	}

	// VS에 상수 버퍼 바인딩
	ID3D11Buffer* cb = m_matrixBuffer.Get();
	ctx->VSSetConstantBuffers(0, 1, &cb);

	// 셰이더 + 메쉬 드로우
	m_basicShader->Bind(m_device);
	mesh.Draw(m_device);
}

void Renderer::EndFrame()
{
	m_device->EndFrame();
}
