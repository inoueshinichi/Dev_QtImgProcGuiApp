#include "main_window.h"

// Standard
#include <iostream>

// Qt
#include <QApplication>

int main(int argc, char** argv)
{
    std::cout << "Hello, world!\n"; 

    QApplication app(argc, argv);

    MainWindow main_win;
    main_win.show();

    return app.exec();
}
