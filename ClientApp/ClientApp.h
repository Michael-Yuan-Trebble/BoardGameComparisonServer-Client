#pragma once

#define IPADDRESS "127.0.0.1"
#define PORT 54000
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "ui_ClientApp.h"

class ClientApp : public QMainWindow
{
    Q_OBJECT

public:
    ClientApp(QWidget *parent = nullptr);
    ~ClientApp();

    SOCKET clientSocket;

    QHBoxLayout* Layout;
    QVBoxLayout* MainLayout;
    QLabel* PortDisplay;

private:

    int createClientSocket();

    void closeAll(SOCKET inSocket);

    void connectSocket();
};

