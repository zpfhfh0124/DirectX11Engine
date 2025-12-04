#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// 기본 버텍스 (position + color)
struct VertexPC
{
	XMFLOAT3 position;
	XMFLOAT3 color;
};

// 행렬 데이터 구조체
struct MatrixBufferData
{
	//XMMATRIX world;
	//XMMATRIX view;
	//XMMATRIX proj;
	XMMATRIX worldViewProj;
};

class GraphicsCommon
{

};

