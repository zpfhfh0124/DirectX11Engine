#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include "GraphicsCommon.h"

using namespace std;

class GraphicsDevice;

class Mesh
{
public:
	bool Initialize(GraphicsDevice* device,
		const vector<VertexPC>& vertices,
		const vector<uint32_t>& indices);

	void Draw(GraphicsDevice* device) const;

	uint32_t GetIndexCount() const { return m_indexCount; }

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	uint32_t m_indexCount = 0;
};

