/**
 * @file directx12_widget.cpp
 * @author your name (you@domain.com)
 * @brief DirectX12 on Qt のテスト
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "directx12_widget.h"

#include <QPalette>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include <iostream>


using Microsoft::WRL::ComPtr;

constexpr int FPS_LIMIT    = 60.0f;
constexpr int MS_PER_FRAME = (int)((1.0f / FPS_LIMIT) * 1000.0f);


/////////////////////////////////////////////////////////////////
// ctor / dtor
/////////////////////////////////////////////////////////////////

DirectX12Widget::DirectX12Widget(QWidget* parent)
    : QWidget(parent)
    , m_iCurrentFrameIndex(0)
    , m_pDevice(nullptr)
    , m_pFactory(nullptr)
    , m_pSwapChain(nullptr)
    , m_pCommandQueue(nullptr)
    , m_pCommandAllocators{}
    , m_pCommandList(nullptr)
    , m_pRTVDescHeap(nullptr)
    , m_iRTVDescSize(0)
    , m_pRTVResources{}
    , m_RTVDescriptors{}
    , m_pSrvDescHeap(nullptr)
    , m_hSwapChainEvent(NULL)
    , m_hFenceEvent(NULL)
    , m_pFence(nullptr)
    , m_iFenceValues{}
    , m_hWnd(reinterpret_cast<HWND>(winId()))
    , m_bDeviceInitialized(false)
    , m_bRenderActive(false)
    , m_bStarted(false)
    , m_BackColor{0.0f, 0.135f, 0.481f, 1.0f}
{
    std::cout << "[DirectX12Widget::DirectX12Widget] - Widget Handle: " << m_hWnd << std::endl;

    QPalette pallet = this->palette();
    pallet.setColor(QPalette::Window, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pallet);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_NativeWindow);

    // Setting these attributes to our widget and returning null on paintEngine event
    // tells Qt that we'll handle all drawing and updating the widget ourselves.
    this->setAttribute(Qt::WA_PaintOnScreen);       // paintEngineイベントを無効
    this->setAttribute(Qt::WA_NoSystemBackground);  // このWidget自身で描画とUpdateを行う
}

DirectX12Widget::~DirectX12Widget() {}



/////////////////////////////////////////////////////////////////
// private
/////////////////////////////////////////////////////////////////

bool DirectX12Widget::init()
{ 
    create3DDevice();

    resetEnvironment();
    
    connect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::onFrame);

    return true;
}

void DirectX12Widget::create3DDevice() 
{
    //////////////////////////////////////////////////////////////////////////////
    // Get Factory
    //////////////////////////////////////////////////////////////////////////////
    UINT factoryFlags = 0;

#ifdef _DEBUG
    {
        ComPtr<ID3D12Debug> dx12Debug;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&dx12Debug))))
        {
            dx12Debug->EnableDebugLayer();

            // Enable additional debug layers.
            factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    DXCall(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&m_pFactory)));


    //////////////////////////////////////////////////////////////////////////////
    // Try and get hardware adapter compatible with d3d12, if not found, use warp.
    //////////////////////////////////////////////////////////////////////////////
    ComPtr<IDXGIAdapter1> adapter;
    getHardwareAdapter(m_pFactory, adapter.GetAddressOf());
    if (!adapter) DXCall(m_pFactory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));

    DXCall(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_pDevice)));


    //////////////////////////////////////////////////////////////////////////////
    // Describe and create the command queue.
    //////////////////////////////////////////////////////////////////////////////
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;
    DXCall(m_pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_pCommandQueue)));


    //////////////////////////////////////////////////////////////////////////////
    // Describe and create the swap-chain.
    //////////////////////////////////////////////////////////////////////////////
    {
        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.BufferCount                 = FRAME_COUNT;
        sd.Width                        = width();
        sd.Height                       = height();
        sd.Format                       = DXGI_FORMAT_R8G8B8A8_UNORM;
        //sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.Flags                        = 0;
        sd.BufferUsage                  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count             = 1;
        sd.SampleDesc.Quality           = 0;
        sd.SwapEffect                   = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode                    = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling                      = DXGI_SCALING_NONE;
        sd.Stereo                       = FALSE;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSd = {};
        fsSd.Windowed = TRUE;

        ComPtr<IDXGISwapChain1> swapChain1;
        DXCall(m_pFactory->CreateSwapChainForHwnd(m_pCommandQueue, m_hWnd, &sd, &fsSd,
                                                 nullptr, swapChain1.GetAddressOf()));
        DXCall(swapChain1->QueryInterface(IID_PPV_ARGS(&m_pSwapChain)));
        m_iCurrentFrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
    }


    //////////////////////////////////////////////////////////////////////////////
    // Create render target view(RTV) descriptor heaps and handles.
    //////////////////////////////////////////////////////////////////////////////
    D3D12_DESCRIPTOR_HEAP_DESC rtvDesc = {};
    rtvDesc.NumDescriptors               = FRAME_COUNT;
    rtvDesc.Type                         = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvDesc.Flags                        = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    DXCall(m_pDevice->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&m_pRTVDescHeap)));
    m_iRTVDescSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_pRTVDescHeap->GetCPUDescriptorHandleForHeapStart());
    
    for (UINT i = 0; i < FRAME_COUNT; ++i)
    {
        m_RTVDescriptors[i] = rtvHandle;
        DXCall(m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pRTVResources[i])));
        m_pDevice->CreateRenderTargetView(m_pRTVResources[i], nullptr, m_RTVDescriptors[i]);
        rtvHandle.Offset(1, m_iRTVDescSize);
    }


    //////////////////////////////////////////////////////////////////////////////
    // Create shader resource view(SRV) descriptor heap.
    //////////////////////////////////////////////////////////////////////////////
    D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
    srvDesc.NumDescriptors = 1;
    srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    DXCall(m_pDevice->CreateDescriptorHeap(&srvDesc, IID_PPV_ARGS(&m_pSrvDescHeap)));


    //////////////////////////////////////////////////////////////////////////////
    // Create command allocator for each frame.
    //////////////////////////////////////////////////////////////////////////////
    for (UINT i = 0; i < FRAME_COUNT; ++i)
    {
        DXCall(m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, 
                                                 IID_PPV_ARGS(&m_pCommandAllocators[i])));
    }


    //////////////////////////////////////////////////////////////////////////////
    // Create command list. We don't create PSO here, so we set it to nullptr to 
    // use the default PSO. Command list by default set on recording state when
    // created, therefore we close it for now.
    //////////////////////////////////////////////////////////////////////////////
    DXCall(m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                        m_pCommandAllocators[m_iCurrentFrameIndex],
                                        nullptr, IID_PPV_ARGS(&m_pCommandList)));
    DXCall(m_pCommandList->Close());


    //////////////////////////////////////////////////////////////////////////////
    // Create synchronized objects.
    //////////////////////////////////////////////////////////////////////////////
    DXCall(m_pDevice->CreateFence(m_iFenceValues[m_iCurrentFrameIndex],
                                  D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence)));

    m_iFenceValues[m_iCurrentFrameIndex]++;
    m_hFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!m_hFenceEvent) DXCall(HRESULT_FROM_WIN32(GetLastError()));

    // DXCall(m_pSwapChain->SetMaximumFrameLatency(FRAME_COUNT));
    // m_hSwapChainEvent = m_pSwapChain->GetFrameLatencyWaitableObject();

    
    //////////////////////////////////////////////////////////////////////////////
    // Wait for the GPU to complete our setup before proceeding.
    //////////////////////////////////////////////////////////////////////////////
    waitForGpu();
}



void DirectX12Widget::getHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter) 
{
    ComPtr<IDXGIAdapter1> adapter;
    *ppAdapter = nullptr;

    for (UINT adapterIndex = 0;
         DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter);
         ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        // Skip software adapter.
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

        // Check to see if the adapter supports Direct3D 12, 
        // but don't create the actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0,
                                        _uuidof(ID3D12Device), nullptr)))
        {
            break;
        }

        *ppAdapter = adapter.Detach();
    }
}



void DirectX12Widget::resizeSwapChain(int width, int height) 
{
    // ReleaseHandle(m_hSwapChainEvent);
    cleanupRenderTarget();

    if (m_pSwapChain) {
        DXCall(m_pSwapChain->ResizeBuffers(FRAME_COUNT, width, height,
                                           DXGI_FORMAT_R8G8B8A8_UNORM, 0));
    }
    else {
        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.BufferCount           = FRAME_COUNT;
        sd.Width                 = width;
        sd.Height                = height;
        sd.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
        // sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.Flags              = 0;
        sd.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count   = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect         = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode          = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling            = DXGI_SCALING_NONE;
        sd.Stereo             = FALSE;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSd = {};
        fsSd.Windowed                        = TRUE;

        ComPtr<IDXGISwapChain1> swapChain;
        DXCall(m_pFactory->CreateSwapChainForHwnd(m_pCommandQueue, m_hWnd, &sd, &fsSd,
                                                  nullptr, swapChain.GetAddressOf()));
        DXCall(swapChain->QueryInterface(IID_PPV_ARGS(&m_pSwapChain)));

        // DXCall(m_pSwapChain->SetMaximumFrameLatency(FRAME_COUNT));
        // m_hSwapChainEvent = m_pSwapChain->GetFrameLatencyWaitableObject();
    }

    createRenderTarget();

    m_iCurrentFrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
}


void DirectX12Widget::cleanupRenderTarget() 
{
    waitForGpu();

    for (UINT i = 0; i < FRAME_COUNT; ++i)
    {
        ReleaseObject(m_pRTVResources[i]);
        m_iFenceValues[i] = m_iFenceValues[m_iCurrentFrameIndex];
    }
}


void DirectX12Widget::createRenderTarget() 
{
    for (UINT i = 0; i < FRAME_COUNT; ++i)
    {
        DXCall(m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pRTVResources[i])));
        m_pDevice->CreateRenderTargetView(m_pRTVResources[i], nullptr, m_RTVDescriptors[i]);
    }
}


void DirectX12Widget::beginScene() 
{
    DXCall(m_pCommandAllocators[m_iCurrentFrameIndex]->Reset());
    DXCall(m_pCommandList->Reset(m_pCommandAllocators[m_iCurrentFrameIndex], nullptr));

    const auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        m_pRTVResources[m_iCurrentFrameIndex], 
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);

    m_pCommandList->ResourceBarrier(1, &barrier);
}


void DirectX12Widget::endScene() 
{
    const auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        m_pRTVResources[m_iCurrentFrameIndex], 
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT);

    m_pCommandList->ResourceBarrier(1, &barrier);

    DXCall(m_pCommandList->Close());
    m_pCommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList * const *>(&m_pCommandList));
    DXCall(m_pSwapChain->Present(1, 0));

    moveToNextFrame();
}

void DirectX12Widget::tick() 
{
    // TODO: Update your scene here. For aesthetics reasons, 
    // only do it here if it's an important component, 
    // otherwise do it in the MainWindow.
    // m_pCamera->Tick();

    emit ticked();
}

void DirectX12Widget::render() 
{
    // Start recording the render commands.
    m_pCommandList->ClearRenderTargetView(m_RTVDescriptors[m_iCurrentFrameIndex],
                                          reinterpret_cast<const float *>(&m_BackColor),
                                          0,
                                          nullptr);

    m_pCommandList->OMSetRenderTargets(1,
                                       &m_RTVDescriptors[m_iCurrentFrameIndex],
                                       FALSE,
                                       nullptr);
    
    m_pCommandList->SetDescriptorHeaps(1, &m_pSrvDescHeap);

    // TODO: Present your scene here. For aesthetics reasons,
    // only do it here if it's an important component, 
    // otherwise do it in the MainWindow.
    // m_pCamera->Apply();

    emit rendered(m_pCommandList);
}


void DirectX12Widget::waitForGpu() 
{
    DXCall(m_pCommandQueue->Signal(m_pFence, m_iFenceValues[m_iCurrentFrameIndex]));

    DXCall(m_pFence->SetEventOnCompletion(m_iFenceValues[m_iCurrentFrameIndex], m_hFenceEvent));

    WaitForSingleObject(m_hFenceEvent, INFINITE);

    m_iFenceValues[m_iCurrentFrameIndex]++;
}


void DirectX12Widget::moveToNextFrame() 
{
    const UINT64 currentFenceValue = m_iFenceValues[m_iCurrentFrameIndex];
    
    DXCall(m_pCommandQueue->Signal(m_pFence, currentFenceValue));

    m_iCurrentFrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
    if (m_pFence->GetCompletedValue() < m_iFenceValues[m_iCurrentFrameIndex])
    {
        DXCall(m_pFence->SetEventOnCompletion(m_iFenceValues[m_iCurrentFrameIndex], m_hFenceEvent));
        WaitForSingleObject(m_hFenceEvent, INFINITE);
    }

    m_iFenceValues[m_iCurrentFrameIndex] = currentFenceValue + 1;
}

LRESULT DirectX12Widget::WndProc(MSG* pMsg)
{
    // Process wheel events using Qt's event-system.
    if (pMsg->message == WM_MOUSEWHEEL || pMsg->message == WM_MOUSEHWHEEL) return false;

    return false;
}

/////////////////////////////////////////////////////////////////
// protected
/////////////////////////////////////////////////////////////////

bool DirectX12Widget::event(QEvent* event) 
{
    switch (event->type())
    {
    case QEvent::Enter:
    case QEvent::FocusIn:
    case QEvent::FocusAboutToChange:
        {
            if (::GetFocus() != m_hWnd)
            {
                QWidget* nativeParent = this;

                while (true)
                {
                    if (nativeParent->isWindow()) break;

                    QWidget* parent = nativeParent->nativeParentWidget();
                    if (!parent) break;

                    nativeParent = parent;
                }

                if (nativeParent && 
                    nativeParent != this &&
                    ::GetFocus() == reinterpret_cast<HWND>(nativeParent->winId()))
                {
                    ::SetFocus(m_hWnd);
                }
            }
        }
        break;
    
    case QEvent::KeyPress:
        emit keyPressed((QKeyEvent *)event);
        break;

    case QEvent::MouseMove:
        emit mouseMoved((QMouseEvent *)event);
        break;
    
    case QEvent::MouseButtonPress:
        emit mousePressed((QMouseEvent *)event);
        break;
    
    case QEvent::MouseButtonRelease:
        emit mouseReleased((QMouseEvent *)event);
        break;
    }


    return QWidget::event(event);
}

void DirectX12Widget::showEvent(QShowEvent* event)
{
    if (!m_bDeviceInitialized)
    {
        // 描画設定開始のエントリーポイント(Widgetが開いてから1回だけ実行)
        // MFCで云うところのOnInitialUpdate()
        m_bDeviceInitialized = init(); // ここで一回だけinit()が呼ばれる.
        emit deviceInitialized(m_bDeviceInitialized);
    }
    return QWidget::showEvent(event);
}

QPaintEngine* DirectX12Widget::paintEngine() const
{
    // DirectX12に描画を任せるのでQtの描画イベントは無視.
    return nullptr;
}

void DirectX12Widget::paintEvent(QPaintEvent* event)
{
    // DirectX12に描画を任せるのでQtの描画エンジンは不使用.
}

void DirectX12Widget::resizeEvent(QResizeEvent* event)
{
    if (m_bDeviceInitialized) {
        onReset();
        emit widgetResized();
    }

    return QWidget::resizeEvent(event);
}

void DirectX12Widget::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().x() == 0)
    {
        // TODO: Update your camera position based on the delta value.
    }
    else if (event->angleDelta().x() != 0)
    {
        // horizontal scrolling - mice with another side scroller.

        // MouseWheelH += (float)(event->angleDelta().y() / WHEEL_DELTA);
    }
    else if (event->angleDelta().y() != 0)
    {
        // MouseWheel += (float)(event->angleDelta().y() / WHEEL_DELTA);
    }

    return QWidget::wheelEvent(event);
}

// https://doc.qt.io/qt-5/qwidget.html#nativeEvent
bool DirectX12Widget::nativeEvent(const QByteArray& eventType, void* message, long* result)
{ 
    Q_UNUSED(eventType);
    Q_UNUSED(result);


#ifdef Q_OS_WIN
    MSG * pMsg = reinterpret_cast<MSG *>(message);
    return WndProc(pMsg);
#endif

    return QWidget::nativeEvent(eventType, message, result);
}

/////////////////////////////////////////////////////////////////
// public
/////////////////////////////////////////////////////////////////

void DirectX12Widget::release() 
{
    m_bDeviceInitialized = false;
    disconnect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::onFrame);
    m_timer.stop();

    waitForGpu();

    for (UINT i = 0; i < FRAME_COUNT; ++i) ReleaseObject(m_pRTVResources[i]);
    ReleaseObject(m_pSwapChain);
    ReleaseHandle(m_hSwapChainEvent);
    ReleaseObject(m_pCommandQueue);
    for (UINT i = 0; i < FRAME_COUNT; ++i) ReleaseObject(m_pCommandAllocators[i]);
    ReleaseObject(m_pCommandList);
    ReleaseObject(m_pRTVDescHeap);
    ReleaseObject(m_pSrvDescHeap);
    ReleaseObject(m_pFence);
    ReleaseHandle(m_hFenceEvent);
    ReleaseObject(m_pDevice);
    ReleaseObject(m_pFactory);
}

void DirectX12Widget::resetEnvironment() 
{
    // TODO: Add your own custom default environment, i.e:
    // m_pCamera->resetCamera();

    onReset();

    if (!m_bRenderActive) {
        tick();
    } 
}

void DirectX12Widget::run() 
{
    /*タイマースタート*/
    m_timer.start(MS_PER_FRAME); // 設定フレームレート間隔で描画更新を依頼する(制御を取りに行く)
    m_bStarted = true;
    m_bRenderActive = true;
}

void DirectX12Widget::pauseFrames()
{
    if (!m_timer.isActive() || !m_bStarted) {
        return;
    }

    disconnect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::onFrame);
    m_timer.stop();
    m_bRenderActive = false;
}

void DirectX12Widget::continueFrames() 
{
    if (m_timer.isActive() || !m_bStarted) {
        return;
    }

    connect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::onFrame);
    m_timer.start(MS_PER_FRAME);
    m_bRenderActive = true;
}

/////////////////////////////////////////////////////////////////
// private slots
/////////////////////////////////////////////////////////////////
void DirectX12Widget::onFrame()
{
    /*Timerで一定間隔で呼び出される*/
    if (m_bRenderActive) {
        tick();
    }

    beginScene();
    render();
    endScene();
}

void DirectX12Widget::onReset() 
{
    // TODO(Gilad): FIXME: this needs to be done in a synchronized manner. 
    // Need to look at DirectX-12 samples here: https://github.com/microsoft/DirectX-Graphics-Samples 
    // how to properly do this without leaking memory.
    pauseFrames();
    resizeSwapChain(this->width(), this->height());
    continueFrames();
}

/////////////////////////////////////////////////////////////////
// public slots
/////////////////////////////////////////////////////////////////
