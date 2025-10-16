#include "ClientApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientApp window;
    window.show();
    return app.exec();
}
