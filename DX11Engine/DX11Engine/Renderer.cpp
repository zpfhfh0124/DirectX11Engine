#include "Renderer.h"
#include "GraphicsDevice.h"

bool Renderer::Initialize(GraphicsDevice* device)
{
	m_device = device;

	m_basicShader = make_unique<Shader>();
	if (!m_basicShader->Initialize(device,
		L"Shaders/BasicVS.hlsl", L"Shaders/BasicPS.hlsl")) 
	{
		return false;
	}

	return true;
}

void Renderer::BeginFrame()
{
	m_device->BeginFrame(0.1f, 0.1f, 0.1f, 1.0f);
}

void Renderer::DrawMesh(const Mesh& mesh)
{
	m_basicShader->Bind(m_device);
	mesh.Draw(m_device);
}

void Renderer::EndFrame()
{
	m_device->EndFrame();
}
