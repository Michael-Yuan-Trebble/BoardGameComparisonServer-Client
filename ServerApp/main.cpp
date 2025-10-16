#include "ServerApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerApp window;
    window.show();
    return app.exec();
}
