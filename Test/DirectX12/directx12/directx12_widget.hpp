/**
 * @file directx12_widget.h
 * @author your name (you@domain.com)
 * @brief DirectX12 on Qt のテスト
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <QWidget>
#include <QTimer>

#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>

#include <stdexception>


class DirectX12Widget : QWidget
{
    Q_OBJECT
public:
     Direct3D12Widget(QWidget * parent);
    virtual ~Direct3D12Widget();

    void release();
    void resetEnvironment();

    void run();
    void parseFrame();
    void continueFrame();

private:
    bool init();
    void create3DDevice();
    void getHardwareAdapter(IDXGIFactory2 *pFactory, IDXGIAdapter1 ** ppAdapter);
    void resizeSwapChain(int width, int height);
    void cleanUpRenderTarget();
    void createRenderTarget();

    void beginScene();
    void endScene();

    void tick();
    void render();

    void waitForGpu();
    void moveToNextFrame();

    LRESULT WIN_API WinProc(MSG *pMsg);

public:
    ID3D12DEVICE *device() const { return m_pDevice; }
    IDXGISwapChain *swapChain() { return m_pSwapChain; }
    ID3D12GraphicsCommandList *commandList() { return m_pCommandList; }

    void setRenderActive(bool isActive) { m_isRenderActive = isActive; }
    D3DCOLORVALUE *backColor() { return &m_backColor; }
  
protected:
    // Qt Event
    bool event(QEvent *event) override;
    void showEvent(QShowEvent *event) override;
    QPaintEngine *paintEngine() const override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;  

// https://doc.qt.io/qt-5/qwidget.html#nativeEvent
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    // Pipeline objects.
    static constexpr int FRAME_COUNT = 3;
    UINT m_iCurrentFrameIndex;

    ID3D12DEVICE *m_pDevice;
    IDXGIFactory4 *m_pFactory;
    IDXGISwapChain3 *m_pSwapChain;
    ID3D12CommandQueue *m_pCommandQueue;
    ID3D12CommandAllocator *m_pCommandAllocators[FRAME_COUNT];
    ID3D12GraphicsCommandList *m_pCommandList;

    // Render Target View
    ID3D12DescriptorHeap *m_pRTVDescHeap;
    UINT m_iRTVDescSize;
    ID3D12Resource *m_pRTVResource[FRAME_COUNT];
    D3D12_CPU_DESCRIPTOR_HANDLE m_rRTVDescriptors[FRAME_COUNT];
    ID3D12DescriptorHeap *m_SrvDescHeap;


    // Synchronization Object
    HANDLE m_hSwapChainEvent;
    HANDLE m_hFenceEvent;
    ID3D12Fence *m_pFence;
    UINT64 m_iFanceValues[FRAME_COUNT];

    // Widget Object
    QTimer m_timer;
    HWND m_hWnd;

    bool m_isDeviceInitialized;
    bool m_isRenderActive;
    bool m_isStarted;
    D3DCOLORVALUE m_backColor;


signals:
    void signalDeviceInitialize(bool isSuccess);
    void signalEventHandle();
    void signalWidgetResize();
    void signalTick();
    void signalRender(ID3D12GraphicsCommandList * pCommandList);
    void signalKeyPress(QKeyEvent *event);
    void signalMouseMove(QMouseEvent *event);
    void signalMousePress(QMouseEvent *event);
    void signalMouseRelease(QMouseEvent *event);

private slots:
    void slotFrame();
    void slotReset();

};


#define RELEASE_OBJECT(object)                                \
    if ((object) != nullptr) {                                \
        object->Release();                                    \
        object = nullptr;                                     \
    }

#define RELEASE_HANDLE(handle)                                \
    if ((handle) != nullptr) {                                \
        CloseHandle(handle);                                  \
        handle = NULL;                                        \
    }


inline std::string get_hr_error_string(HRESULT hr) {
    
    int size = std::snprintf(nullptr, 0, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    if (size < 0) {
        std::printf("Fatal error: std::snprintf() in get_hr_error_string.\n");
        std::abort();
    }
    /* バッファサイズを算出(文字列長 + null文字サイズ) */
    size_t buf_size = size + sizeof(char);

    /* バッファサイズ分メモリ確保 */
    std::vector<char> buf(buf_size);

    /* 文字列のフォーマット */
    std::snprintf(buf.data(), buf_size, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    
    /* 文字列をstd::string型に変換して出力 */
    return std::string(buf.data(), buf.data() + size);
}

///////////////////////////////////////////////////////////////////////
// HRESULT HANDLE Exception クラス
///////////////////////////////////////////////////////////////////////
class HrException : public std::exception
{
protected:
    error_code code_;
    string full_msg_; // 表示されるFullメッセージ
    string msg_;      // エラーメッセージ
    string func_;     // エラーが発生した関数名
    string file_;     // エラーが発生したファイル名
    int line_;        // エラーが発生した行番号

    HRESULT m_hResult;

public:
    HrException(HRESULT hr, const string &msg, const string &func, 
                const string &file, int line)
        : m_hResult(hr), msg_(msg), func_(func), file_(file), line_(line)
        {
            std::ostringstream ss;
            ss << get_hr_error_string(m_hResult) << " in "
               << func_ << std::endl
               << file_ << ":" << line_ << std::endl
               << msg_ << std::endl;
            full_msg_ = ss.str();
        }

    virtual ~HrException() throw() {}

    virtual const char *what() const throw() {
        return full_msg_.c_str();
    }

    HHANDLE error() const { return m_hResult; }
};


#define HR_ERROR(hr, msg, ...)                                                   \
    throw HrException(hr, format_string(msg, ##__VA_ARGS__),                     \
        __func__, __FILE__, __LINE__);

#define HR_CHECK(hr, msg, ...)                                                   \
    if (FAILED(hr)) {                                                            \
        HR_ERROR(hr, string("Failed `" #hr "`: ") + msg, ##__VA_ARGS__)          \
    }

#define HR_FORCE_ASSERT(hr, msg, ...)                                            \
    if (FAILED(hr)) {                                                            \
        std::cerr << "Aborting: " << format_string(msg, ##__VA_ARGS__)           \
                  << " at " << __func__                                          \
                  << " in " << __FILE__                                          \
                  << ":" << __LINE__                                             \
                  << std::endl;                                                  \
        ::abort();                                                               \
    }