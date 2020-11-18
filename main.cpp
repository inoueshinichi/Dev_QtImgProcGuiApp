#include "pch.hpp"
// #include "windows/win_console.hpp"
#include "main_window.hpp"

#include <QApplication>


int main(int argc, char** argv)
{

    // Is::Win32Console console(8, 8);

    std::cout << "Hello, world!\n"; 

    QApplication app(argc, argv);

    MainWindow main_win;
    main_win.show();

    return app.exec();
}
