#include "GraphicsDevice.h"

bool GraphicsDevice::Initialize(HWND hwnd, int width, int height)
{
    // null 체크
    if (hwnd == nullptr || !IsWindow(hwnd))
    {
        MessageBoxW(nullptr, L"GraphicsDevice::Initialize - 잘못된 HWND", L"DX11 Error", MB_OK);
        return false;
    }

    if (width <= 0 || height <= 0)
    {
        wchar_t buf[256];
        swprintf_s(buf, 256, L"잘못된 화면 크기: %d x %d", width, height);
        MessageBoxW(nullptr, buf, L"DX11 Error", MB_OK);
        return false;
    }

    // 스왑 체인 / 디바이스 생성
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    UINT deviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        deviceFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        &sd,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        nullptr,//&featureLevel,
        m_context.GetAddressOf()
    );

    if (FAILED(hr)) 
    {
        wchar_t buf[256];
        swprintf_s(buf, 256, L"D3D11CreateDeviceAndSwapChain 실패\nHRESULT = 0x%08X", hr);
        MessageBox(hwnd, buf, L"DX11 Error", MB_OK);
        return false;
    }

    // 백버퍼에서 RenderTargetView 생성
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    if (FAILED(hr))
        return false;

    hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_rtv.GetAddressOf());
    if (FAILED(hr))
        return false;

    // DepthStencil 버퍼/뷰 생성
    D3D11_TEXTURE2D_DESC depthDesc{};
    depthDesc.Width     = width;
    depthDesc.Height    = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count      = 1;
    depthDesc.SampleDesc.Quality    = 0;
    depthDesc.Usage     = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags    = 0;
    depthDesc.MiscFlags         = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthBuffer;
    hr = m_device->CreateTexture2D(&depthDesc, nullptr, depthBuffer.GetAddressOf());
    if (FAILED(hr))
        return false;

    hr = m_device->CreateDepthStencilView(depthBuffer.Get(), nullptr, m_dsv.GetAddressOf());
    if (FAILED(hr))
        return false;

    // 렌더 타겟 깊이 버퍼 바인딩 + 뷰포트 설정
    m_context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), m_dsv.Get());

    D3D11_VIEWPORT vp{};
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    m_context->RSSetViewports(1, &vp);

    return true;
}

void GraphicsDevice::BeginFrame(float r, float g, float b, float a)
{
    float clearColor[4] = { r, g, b, a };

    m_context->ClearRenderTargetView(m_rtv.Get(), clearColor);

    if (m_dsv)
        m_context->ClearDepthStencilView(m_dsv.Get(), D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::EndFrame()
{
    m_swapChain->Present(1, 0);
}
