#include "TestBothApplications.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestBothApplications window;
    window.show();
    return app.exec();
}
