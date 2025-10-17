#include <QtWidgets/QApplication>
#include <qmessagebox.h>
#include <qicon.h>
#include "Navigator.h"
#include "NetworkManager.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/ClientIcon.ico"));

    QFile styleFile(":/StyleSheet.qss");
    if (styleFile.open(QFile::ReadOnly)) 
    {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
    }
    else 
    {
        QMessageBox::warning(
            nullptr,
            "Warning",
            "Warning, Style Sheet Failed to load, may result in cosmetic oddities",
            QMessageBox::Ok
        );
    }

    NetworkManager* network = new NetworkManager();
    FileManager* fileManager = new FileManager();
    if (network && fileManager && network->init()) 
    {
        Navigator* nav = new Navigator();
        nav->start(network, fileManager);
        return app.exec();
    }
    else 
    {
        QMessageBox::warning(
            nullptr,
            "Warning",
            "Warning, Initialization Failed",
            QMessageBox::Ok | QMessageBox::Cancel
        );
        return -1;
    }
}
