#include "main_window.h"

#include "camera_controller.h"

#include <memory>
#include <thread>
#include <chrono>

#include <QApplication>

int main(int argc, char** argv)
{
    std::cout << "Hello, world!\n"; 

    QApplication app(argc, argv);

    auto appVer = QCoreApplication::applicationVersion();
    auto appName = QCoreApplication::applicationName();
    auto appOrgDomain = QCoreApplication::organizationDomain();
    auto appOrgName = QCoreApplication::organizationName();
    auto appDirPath = QCoreApplication::applicationDirPath();
    auto appFilePath = QCoreApplication::applicationFilePath();
    auto appPid = QCoreApplication::applicationPid();

    auto appDispName = QGuiApplication::applicationDisplayName();
    auto appPlatformName = QGuiApplication::platformName();
    auto appDesktopFilename = QGuiApplication::desktopFileName();
    auto appPrimeScreen = QGuiApplication::primaryScreen();
    auto appScreens = QGuiApplication::screens();
    auto appWinIcon = QGuiApplication::windowIcon();
    auto appPalette = QGuiApplication::palette();

    auto appStyleSheet = app.styleSheet();

    MainWindow main_win;
    main_win.show();

    // CameraControllerテスト
    CameraController camCtrl;
    camCtrl.setCameraType("general", "usb");
    camCtrl.startCamera(0, 50);

    camCtrl.fetchFrame();   

    std::this_thread::sleep_for(std::chrono::seconds(5));
 

    camCtrl.stopCamera();

    return app.exec();
}
