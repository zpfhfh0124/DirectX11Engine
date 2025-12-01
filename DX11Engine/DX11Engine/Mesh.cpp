#include "Mesh.h"
#include "GraphicsDevice.h"

bool Mesh::Initialize(GraphicsDevice* device, const vector<VertexPC>& vertices, const vector<uint32_t>& indices)
{
	if (vertices.empty() || indices.empty())
		return false;

    m_indexCount = indices.size();

    // 버텍스 버퍼 생성
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.ByteWidth = UINT(sizeof(VertexPC) * vertices.size());
    vbDesc.Usage = D3D11_USAGE_DEFAULT;
    vbDesc.CPUAccessFlags = 0;
    vbDesc.MiscFlags = 0;
    vbDesc.StructureByteStride = sizeof(VertexPC);

    D3D11_SUBRESOURCE_DATA vbData = {};
    vbData.pSysMem = vertices.data();
    vbData.SysMemPitch = 0;
    vbData.SysMemSlicePitch = 0;

    HRESULT result = device->GetDevice()->CreateBuffer(&vbDesc, &vbData, m_vertexBuffer.GetAddressOf());

    if (result != S_OK)
        return false;

    // 인덱스 버퍼 생성
	D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.ByteWidth = UINT(sizeof(uint32_t) * indices.size());
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.CPUAccessFlags = 0;
    ibDesc.MiscFlags = 0;
    ibDesc.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA ibData = {};
	ibData.pSysMem = indices.data();
	ibData.SysMemPitch = 0;
	ibData.SysMemSlicePitch = 0;

	result = device->GetDevice()->CreateBuffer(&ibDesc, &ibData, m_indexBuffer.GetAddressOf());

	if (result != S_OK)
		return false;

    return true;
}

void Mesh::Draw(GraphicsDevice* device) const
{
    ID3D11DeviceContext* ctx = device->GetContext();

    // 버텍스 버퍼 바인딩
    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    ID3D11Buffer* vb = m_vertexBuffer.Get();
    ctx->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

    // 인덱스 버퍼 바인딩
    ctx->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 프리미티브 타입 설정 (삼각형 리스트)
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 그리기
    ctx->DrawIndexed(m_indexCount, 0, 0);
}
