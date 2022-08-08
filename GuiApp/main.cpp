#include "main_window.h"
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

  
    return app.exec();
}
