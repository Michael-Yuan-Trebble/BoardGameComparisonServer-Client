#include <QtWidgets/QApplication>
#include "Navigator.h"
#include "NetworkManager.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile styleFile(":/StyleSheet.qss");
    if (styleFile.open(QFile::ReadOnly)) 
    {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
    }

    NetworkManager* network = new NetworkManager();
    FileManager* fileManager = new FileManager();
    if (network && fileManager && network->init()) {
        Navigator* nav = new Navigator();
        nav->start(network, fileManager);
    }
    else {
        // TODO: Put an error trying to set it up
    }
    return app.exec();
}
