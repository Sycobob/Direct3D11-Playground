#pragma once

#include <wrl\client.h>
#include <DirectXMath.h>

#include "GameTimer.h"

class RendererBase
{
public:
	RendererBase();
	virtual ~RendererBase();

	virtual bool Initialize(HWND);
	virtual bool Resize();
	virtual bool Update(const GameTimer&);
	virtual bool Render();
	virtual void Teardown();

protected:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT4 = DirectX::XMFLOAT4;

	HWND hwnd = nullptr;

	void SetHwnd(HWND);
	bool InitializeDevice();
	bool InitializeDebugOptions();
	bool CheckForWarpDriver();
	bool ObtainDXGIFactory();
	bool isInitialized = false;
	ComPtr<ID3D11Device>        pD3DDevice;
	ComPtr<ID3D11DeviceContext> pD3DImmediateContext;
	ComPtr<IDXGIFactory1>       pDXGIFactory;

	bool InitializeSwapChain();
	bool GetWindowClientSize(UINT&, UINT&);
	bool CreateBackBufferView();
	bool UpdateAllowFullscreen();
	ComPtr<IDXGISwapChain>         pSwapChain;
	ComPtr<ID3D11RenderTargetView> pRenderTargetView;

	bool InitializeDepthBuffer();
	ComPtr<ID3D11DepthStencilView> pDepthBufferView;

	void InitializeOutputMerger();
	void InitializeViewport();

	void UpdateFrameStatistics(const GameTimer&);
	double averageFrameTime = 0;

	bool LogAdapters();
	bool LogOutputs(ComPtr<IDXGIAdapter1>);
	bool LogDisplayModes(ComPtr<IDXGIOutput>);
	bool LogLiveObjects();

	/* NOTE:
	 * DirectX throws exceptions if multiSampleCount > 1 when entering fullscreen. These
	 * are first chance exceptions that get handled internally. Still, they're annoying.
	 */

	//TODO: Encapsulate in a struct?
	//Settings
	bool     startFullscreen  = false;
	bool     allowFullscreen  = true;
	UINT     numQualityLevels = 0;
	UINT     multiSampleCount = 1;
	UINT     width            = 800;
	UINT     height           = 600;
	XMFLOAT4 backgroundColor  = XMFLOAT4();

private:
	RendererBase(const RendererBase&) = delete;
	RendererBase& operator =(const RendererBase&) = delete;
};