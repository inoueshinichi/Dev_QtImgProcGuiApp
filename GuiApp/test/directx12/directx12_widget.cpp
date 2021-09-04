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

using Microsoft::WRL::ComPtr;

constexpr int FPS_LIMIT    = 60.0f;
constexpr int MS_PER_FRAME = (int)((1.0f / FPS_LIMIT) * 1000.0f);

#include <directx12_widget.hpp>

/////////////////////////////////////////////////////////////////
// ctor / dtor
/////////////////////////////////////////////////////////////////

DirectX12Widget::DirectX12Widget(QWidget *parent)
    : QWidget(parent)
    , m_iCurrentFrameIndex(0)
    , m_pDevice(nullptr)
    , m_pFactory(nullptr)
    , m_pSwapChain(nullptr)
    , m_pCommandQueue(nullptr)
    , m_pCommandAllocators{}
    , m_pCommandQueueList(nullptr)
    , m_pRTVDescHeap(nullptr)
    , m_iRTVDescSize(0)
    , m_pRTVResources{}
    , m_rRTVDescriptors{}
    , m_pSrvDescHeap(nullptr)
    , m_hSwapChainEvent(NULL)
    , m_hFenceEvent(NULL)
    , m_pFence(nullptr)
    , m_iFenceValues{}
    , m_hWnd(reinterpret_cast<HWND>(winId()))
    , m_isDeviceInitialized(false)
    , m_isRenderActive(false)
    , m_isStarted(false)
    , m_backColor{0.0f, 0.135f, 0.481f, 1.0f}
{
    QPallet pallet = this->pallet();
    pallet.setColor(QPallet::Window, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pallet);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_NativeWindow);

    // Setting these attributes to our widget and returning null on paintEngine event
    // tells Qt that we'll handle all drawing and updating the widget ourselves.
    this->setAttribute(Qt::WA_PaintOnScreen);
    this->setAttribute(Qt::WA_NoSystemBackground);
}

DirectX12Widget::~DirectX12Widget() {}



/////////////////////////////////////////////////////////////////
// private
/////////////////////////////////////////////////////////////////

bool DirectX12Widget::init()
{ 
    create3DDevice();
    resetEnvironment();
    
    this->connect(&m_timer, &QTimer::timeout, this, &slotFrame);

    return true;
}

void DirectX12Widget::create3DDevice() {}
void DirectX12Widget::getHardwareAdapter(IDXGIFactory2 *pFactory, IDXGIAdapter1 **ppAdapter) {}
void DirectX12Widget::resizeSwapChain(int width, int height) {}
void DirectX12Widget::cleanUpRenderTarget() {}
void DirectX12Widget::createRenderTarget() {}
void DirectX12Widget::beginScene() {}
void DirectX12Widget::endScene() {}

void DirectX12Widget::tick() 
{
    // TODO: Update your scene here. For aesthetics reasons, only do it here if it's an
    // important component, otherwise do it in the MainWindow.
    // m_pCamera->Tick();

    emit signalTicked();
}

void DirectX12Widget::render() {}
void DirectX12Widget::waitForGpu() {}
void DirectX12Widget::moveToNextFrame() {}

LRESULT Direct3D12Widget::WndProc(MSG * pMsg)
{
    // Process wheel events using Qt's event-system.
    if (pMsg->message == WM_MOUSEWHEEL || pMsg->message == WM_MOUSEHWHEEL) return false;

    return false;
}

/////////////////////////////////////////////////////////////////
// protected
/////////////////////////////////////////////////////////////////

bool DirectX12Widget::event(QEvent *event) 
{
    return QWidget::event(event);
}

void DirectX12Widget::showEvent(QShowEvent *event)
{
    if (!m_isDeviceInitialized)
    {
        // 描画設定開始のエントリーポイント(Widgetが開いてから1回だけ実行)
        // MFCで云うところのOnInitialUpdate()
        m_isDeviceInitialized = init();
        emit deviceInitialized(m_isDeviceInitialized);
    }
    return QWidget::showEvent(event);
}

QPaintEngine *DirectX12Widget::paintEngine()
{
    // DirectX12に描画を任せるのでQtの描画イベントは無視.
    return nullptr;
}

void DirectX12Widget::paintEvent(QPaintEvent *event)
{
    // DirectX12に描画を任せるのでQtの描画エンジンは不使用.
}

void DirectX12Widget::resizeEvent(QResizeEvent *event)
{
    if (m_isDeviceInitialized) {
        slotReset();
        emit signalWidgetResized();
    }

    return QWidget::resizeEvent(event);
}

void DirectX12Widget::wheelEvent(QWheelEvent *event)
{
    return QWidget::wheelEvent(event);
}

// https://doc.qt.io/qt-5/qwidget.html#nativeEvent
bool DirectX12Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{  
#ifdef Q_OS_WIN
    MSG * pMsg = reinterpret_cast<MSG *>(message);
    return WndProc(pMsg);
#endif

    return QWidget::nativeEvent(eventType, message, result);
}

/////////////////////////////////////////////////////////////////
// public
/////////////////////////////////////////////////////////////////

void DirectX12Widget::release() {}

void DirectX12Widget::resetEnvironment() 
{
     // TODO: Add your own custom default environment, i.e:
    // m_pCamera->resetCamera();

    slotReset();

    if (!m_bRenderActive) {
        tick();
    } 
}

void DirectX12Widget::run() 
{
    /*タイマースタート*/
    // 設定フレームレート間隔で描画更新を依頼する(制御を取りに行く)
    m_timer.start(MS_PER_FRAME);
    m_isStarted = true;
    m_isRenderActive = true;
}

void DirectX12Widget::parseFrame()
{
    if (!m_timer.isActive() || !m_isStarted) {
        return;
    }
    this->disconnect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::slotFrame);
    m_timer.slop();
    m_isRenderActive = false;
}

void DirectX12Widget::continueFrame() 
{
    if (!m_timer.isActive() || !m_isStarted) {
        return;
    }
    this->connect(&m_timer, &QTimer::timeout, this, &DirectX12Widget::slotFrame);
    m_timer.start(MS_PER_FRAME);
    m_isRenderActive = true;
}

/////////////////////////////////////////////////////////////////
// private slots
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// public slots
/////////////////////////////////////////////////////////////////
void DirectX12Widget::slotFrame()
{
    if (m_isRenderActive) {
        tick();
    }

    begineScene();
    render();
    endScene();
}

void DirectX12Widget::slotReset() 
{
    // TODO(Gilad): FIXME: this needs to be done in a synchronized manner. Need to look at
    // DirectX-12 samples here: https://github.com/microsoft/DirectX-Graphics-Samples how to
    // properly do this without leaking memory.
    pauseFrame();
    resizeSwapChain(this->width(), this->height());
    continueFrame();
}