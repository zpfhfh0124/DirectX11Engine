#pragma once
#include <memory>
#include "Shader.h"
#include "Mesh.h"

using namespace std;

class GraphicsDevice;

class Renderer
{
public:
	bool Initialize(GraphicsDevice* device);

	void BeginFrame();
	void EndFrame();

	void DrawMesh(const Mesh& mesh);

private:
	GraphicsDevice*		m_device = nullptr;
	unique_ptr<Shader>  m_basicShader;
	// 조명용 constant buffer, 카메라 정보 등 추가 예정
};

