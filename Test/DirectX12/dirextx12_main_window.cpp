#include <directx12_main_window.hpp>

#include <QTime>
#include <QCoreApplication>

DirectX12MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUi(new Ui::DirectX12MainWindow())
{
    // UI
    m_pUi->setupUi(this);

    void signalDeviceInitialize(bool isSuccess);
    void signalEventHandle();
    void signalWidgetResize();
    void signalTicke();
    void signalRendere(ID3D12GraphicsCommandList * pCommandList);
    void signalKeyPresse(QKeyEvent *event);
    void signalMouseMove(QMouseEvent *event);
    void signalMousePresse(QMouseEvent *event);
    void signalMouseRelease(QMouseEvent *event);

    this->connect(m_pUi->directX12View, &DirectX12Widget::signalDeviceInitialize,
        this, &DirectX12MainWindow::slotDeviceInitialize);
    this->connect(m_pUi->directX12View, &DirectX12Widget::signalTick,
        this, &DirectX12MainWindow::slotTick);
    this->connect(m_pUi->directX12View, &DirectX12Widget::signalRender,
        this, &DirectX12MainWindow::slotRender);

}

DirectX12MainWindow::~DirectX12MainWindow()
{
    if (m_pUi) {
        delete m_pUi;
        m_pUi = nullptr;
    }
}

void DirectX12MainWindow::closeEvent(QCloseEvent *event)
{
    // Qtイベントにこれ以上イベント通知が送られて来ないようにする.
    event->ignore();

    m_pUi->directx12Widget->release();

    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    // Qtイベントの通知再開
	event->accept();
}

void DirectX12MainWindow::slotDeviceInitialize(bool isSuccess)
{


    QTimer::singleShot(500, this, [&] { m_pUi->directX12Widget->run(); });
}

void DirectX12MainWindow::slotTick()
{

}

void DirectX12MainWindow::slotRender()
{

}