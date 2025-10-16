#pragma once

#define IPADDRESS "127.0.0.1"
#define PORT 54000
#include <iostream>
#include <WinSock2.h>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <qobject.h>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include "ui_ClientApp.h"
#include "NetworkManager.h"

class ClientApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientApp(NetworkManager* inNet, QWidget *parent = nullptr);
    ~ClientApp();

    SOCKET clientSocket;

    QHBoxLayout* Layout;
    QVBoxLayout* MainLayout;
    QLabel* PortDisplay;
    QPushButton* connectBtn;
    QLabel* ConnectedLabel;

signals:
    void connectedServer();

private:

    NetworkManager* network;

    void connectSocket();
};

