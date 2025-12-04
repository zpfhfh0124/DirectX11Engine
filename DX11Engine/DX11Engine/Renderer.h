#pragma once
#include <memory>
#include <wrl.h>
#include <d3d11.h>
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

using namespace std;

class GraphicsDevice;

class Renderer
{
public:
	bool Initialize(GraphicsDevice* device, int width, int height);

	void BeginFrame();
	void EndFrame();
	void DrawMesh(const Mesh& mesh);

	Camera& GetCamera() { return m_camera; }

private:
	GraphicsDevice*		m_device = nullptr;
	
	// 조명용 constant buffer, 카메라 정보 등
	unique_ptr<Shader> m_basicShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_matrixBuffer;
	Camera m_camera;
};

