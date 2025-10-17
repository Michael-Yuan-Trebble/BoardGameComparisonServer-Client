#include "ServerApp.h"
#include <QtWidgets/QApplication>
#include <qicon.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/ServerIcon.ico"));
    ServerApp window;
    window.show();
    return app.exec();
}
